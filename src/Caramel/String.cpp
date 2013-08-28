// Caramel C++ Library - String Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Functional/ScopeExit.h>
#include <Caramel/String/Algorithm.h>
#include <Caramel/String/Sprintf.h>
#include <Caramel/String/SprintfManager.h>
#include <Caramel/String/Utf8String.h>

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )
#include <Caramel/Windows/WideString.h>
#endif

#include <boost/algorithm/string/trim.hpp>
#include <codecvt>
#include <cstdarg>
#include <cstdio>


namespace Caramel
{

//
// Contents
//
//   Sprintf
//   SprintfBuffer
//   SprintfManager
//   Utf8String
//   Algorithm
//

///////////////////////////////////////////////////////////////////////////////
//
// Sprintf
//
// - CAUTION: Sprintf utility is the foundation of Exception and Trace macros.
//            Don't use these macros in Sprintf code.
//

namespace Detail
{

std::string SprintfImpl( const Char* format, ... )
{
    SprintfBuffer* buffer = SprintfManager::Instance()->AllocateBuffer();
    auto guard = ScopeExit( [ buffer ] { SprintfManager::Instance()->FreeBuffer( buffer ); } );

    Char* p = buffer->GetPointer();

    va_list args;
    va_start( args, format );

    const Int count = vsnprintf( p, SprintfBuffer::SIZE, format, args );

    va_end( args );

    if ( 0 > count )
    {
        // TODO: use Trace function for error reporting.
    }
    
    return std::string( p );
}

} // namespace Detail


///////////////////////////////////////////////////////////////////////////////
//
// Sprintf Buffer
//
// - CAUTION: Sprintf utility is the foundation of Exception and Trace macros.
//            Don't use these macros in Sprintf code.
//

SprintfBuffer::SprintfBuffer()
{
    // Align buffer acoording to the cache lines
    Void* p = &m_chunk[0];
    std::size_t space = CHUNK_SIZE;
    m_buffer = reinterpret_cast< Char* >( std::align( BUFFER_ALIGN, SIZE, p, space ));

    CARAMEL_ASSERT( m_buffer + SIZE + sizeof( Uint32 ) <= &m_chunk[ CHUNK_SIZE ] );

    // Padding before head
    std::fill( &m_chunk[0], m_buffer, PAD_CHAR );

    // Clear the buffer
    std::fill( m_buffer, m_buffer + SIZE, 0 );

    // Put the tail guard
    Uint32* tailGuard = reinterpret_cast< Uint32* >( m_buffer + SIZE );
    *tailGuard = TAIL_GUARD;

    // Padding after tail
    std::fill( m_buffer + SIZE + sizeof( Uint32 ), &m_chunk[ CHUNK_SIZE ], PAD_CHAR );
}


Bool SprintfBuffer::CheckGuard() const
{
    return *reinterpret_cast< Uint32* >( m_buffer + SIZE ) == TAIL_GUARD;
}


///////////////////////////////////////////////////////////////////////////////
//
// Sprintf Manager
//
// - CAUTION: Sprintf utility is the foundation of Exception and Trace macros.
//            Don't use these macros in Sprintf code.
//

SprintfManager::SprintfManager()
    : m_buffers( 1 )   // <= Number of free-list nodes.
{                      //    Nodes may be allocated dynamically when necessary,
}                      //    Give only 1 node for the first call is OK.


SprintfManager::~SprintfManager()
{
    SprintfBuffer* buffer = nullptr;
    while ( m_buffers.pop( buffer ))
    {
        delete buffer;
    }
}


SprintfBuffer* SprintfManager::AllocateBuffer()
{
    SprintfBuffer* buffer = nullptr;
    if ( ! m_buffers.pop( buffer ))
    {
        buffer = new SprintfBuffer;
    }

    CARAMEL_ASSERT( buffer->CheckGuard() );
    return buffer;
}


void SprintfManager::FreeBuffer( SprintfBuffer* buffer )
{
    CARAMEL_VERIFY( m_buffers.push( buffer ));
}


///////////////////////////////////////////////////////////////////////////////
//
// UTF-8 String
//

Utf8String::Utf8String()
{
}


Utf8String::Utf8String( Char c )
{
    if ( 0x7f < static_cast< Uint8 >( c ))
    {
        CARAMEL_THROW( "Input c is not valid UTF-8 character" );
    }

    m_s.assign( 1, c );
}


Utf8String::Utf8String( const std::string& u8Text )
{
    if ( !this->TryParse( u8Text ))
    {
        CARAMEL_THROW( "Input text is not UTF-8 encoded" );
    }
}


//
// Validation
//

inline static Int Utf8String_CalculateNumTrails( Byte lead )
{
    if ( 0 == ( lead & 0x80 ))  //  0dddddddd
    {
        return 0;
    }
    else if ( 0xC0 == ( lead & 0xE0 ))  // 110ddddd
    {
        return 1;
    }
    else if ( 0xE0 == ( lead & 0xF0 ))  // 1110dddd
    {
        return 2;
    }
    else if ( 0xF0 == ( lead & 0xF8 ))  // 11110ddd
    {
        return 3;
    }
    else
        return -1;
}


inline static Bool Utf8String_IsTrail( Byte b )
{
    return ( 0x80 == ( b & 0xC0 ));  // 10dddddd
}


Bool Utf8String::TryParse( const std::string& u8Text )
{
    Uint pos = 0;

    while ( u8Text.length() > pos )
    {
        Int num = Utf8String_CalculateNumTrails( static_cast< Byte >( u8Text[ pos ++ ] ));
        
        // not valid leading character
        if ( 0 > num ) { return false; }
        
        // not enough length
        if ( u8Text.length() < pos + num ) { return false; }

        while ( 0 < num -- )
        {
            // not trailing character
            if ( ! Utf8String_IsTrail( static_cast< Byte >( u8Text[ pos ++ ] ))) { return false; }
        }
    }

    m_s.assign( u8Text );
    return true;
}


Bool Utf8String::TryParse( const Byte* data, Uint length )
{
    CARAMEL_NOT_IMPLEMENTED();
}


//
// Conversion between UTF-8 and other Multi-bytes encoding.
//

Bool Utf8String::TryParse( const std::string& text, TextEncoding encoding )
{
    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    {
        Windows::WideString wbuffer;

        if ( ! wbuffer.TryParse( text, encoding ))
        {
            return false;
        }

        m_s.assign( wbuffer.ToNarrow( TEXT_ENCODING_UTF8 ));
        return true;
    }
    #else
    {
        CARAMEL_NOT_IMPLEMENTED();   
    }
    #endif
}


//
// Conversion between UTF-8 and UTF-16 LE, Windows specific
//

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

Utf8String::Utf8String( const std::wstring& wText )
{
    std::wstring_convert< std::codecvt_utf8_utf16< Wchar > > converter;
    m_s.assign( converter.to_bytes( wText ));
}


std::wstring Utf8String::ToWstring() const
{
    std::wstring_convert< std::codecvt_utf8_utf16< Wchar > > converter;
    return converter.from_bytes( static_cast< const std::string& >( m_s ));
}

#endif // CARAMEL_SYSTEM_IS_WINDOWS


//
// Operators
//

Utf8String& Utf8String::operator+=( const Utf8String& rhs )
{
    m_s += rhs.m_s;
    return *this;
}


///////////////////////////////////////////////////////////////////////////////
//
// String Algorithm
//

static const std::string::size_type STRING_NPOS = -1;


//
// Predicates
//

Bool Contains( const std::string& s, Char c )
{
    return STRING_NPOS != s.find_first_of( c );
}


Bool EndsWith( const std::string& s, Char c )
{
    if ( s.empty() ) { return false; }
    return c == s[ s.length() - 1 ];
}


//
// Extractors
//

std::string BeforeFirst( const std::string& s, Char c )
{
    const Uint pos = s.find_first_of( c );
    return STRING_NPOS == pos ? s
                              : s.substr( 0, pos );
}


std::string AfterFirst( const std::string& s, Char c )
{
    const Uint pos = s.find_first_of( c );
    return STRING_NPOS == pos ? std::string()
                              : s.substr( pos + 1 );
}


//
// Manipulators
//

void Trim( std::string& s )
{
    boost::algorithm::trim( s );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
