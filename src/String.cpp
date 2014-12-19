// Caramel C++ Library - String Facility - Implementation

#include "CaramelPch.h"

#include "String/FormatterImpl.h"
#include "String/SprintfManager.h"
#include <Caramel/Functional/ScopeExit.h>
#include <Caramel/Lexical/Integer.h>
#include <Caramel/String/Algorithm.h>
#include <Caramel/String/Format.h>
#include <Caramel/String/Sprintf.h>
#include <Caramel/String/ToString.h>
#include <Caramel/String/Utf8String.h>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/range/irange.hpp>
#include <cstdarg>
#include <cstdio>
#include <sstream>

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )
#include <Caramel/Windows/WideString.h>
#include <codecvt>
#endif


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
//   ToString
//   ToStringT
//   Formatter
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
    // Keep a local copy here.
    // Using PAD_CHAR in std::fill() would cause a linking error in Clang compiler.
    const Uint8 padding = PAD_CHAR;

    // Align buffer acoording to the cache lines
    Void* p = &m_chunk[0];

    #if defined( CARAMEL_SYSTEM_IS_ANDROID )
    {
        // As at Nov.2013, Andoird NDK GNU C++ 4.8 doesn't support std::align
        m_buffer = reinterpret_cast< Char* >( p );
    }
    #else
    {
        std::size_t space = CHUNK_SIZE;
        m_buffer = reinterpret_cast< Char* >( std::align( BUFFER_ALIGN, SIZE, p, space ));
    }
    #endif

    CARAMEL_ASSERT( m_buffer + SIZE + sizeof( Uint32 ) <= &m_chunk[ CHUNK_SIZE ] );

    // Padding before head
    std::fill( &m_chunk[0], m_buffer, padding );

    // Clear the buffer
    std::fill( m_buffer, m_buffer + SIZE, 0 );

    // Put the tail guard
    Uint32* tailGuard = reinterpret_cast< Uint32* >( m_buffer + SIZE );
    *tailGuard = TAIL_GUARD;

    // Padding after tail
    std::fill( m_buffer + SIZE + sizeof( Uint32 ), &m_chunk[ CHUNK_SIZE ], padding );
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
{
}


SprintfManager::~SprintfManager()
{
    SprintfBuffer* buffer = nullptr;
    while ( m_buffers.TryPop( buffer ))
    {
        delete buffer;
    }
}


SprintfBuffer* SprintfManager::AllocateBuffer()
{
    SprintfBuffer* buffer = nullptr;
    if ( ! m_buffers.TryPop( buffer ))
    {
        buffer = new SprintfBuffer;
    }

    CARAMEL_ASSERT( buffer->CheckGuard() );
    return buffer;
}


void SprintfManager::FreeBuffer( SprintfBuffer* buffer )
{
    m_buffers.Push( buffer );
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


Bool Utf8String::Validate( const std::string& u8Text )
{
    Usize pos = 0;

    while ( u8Text.length() > pos )
    {
        Int num = Utf8String_CalculateNumTrails( static_cast< Byte >( u8Text[ pos ++ ] ));
        
        // not valid leading character
        if ( num < 0 ) { return false; }
        
        // not enough length
        if ( u8Text.length() < pos + num ) { return false; }

        while (( num -- ) > 0 )
        {
            // not trailing character
            if ( ! Utf8String_IsTrail( static_cast< Byte >( u8Text[ pos ++ ] ))) { return false; }
        }
    }

    return true;
}


//
// Conversions
//

Bool Utf8String::TryParse( const std::string& u8Text )
{
    const Bool u8Encoded = Validate( u8Text );
    if ( u8Encoded )
    {
        m_s.assign( u8Text );
    }
    return u8Encoded;
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

inline boost::integer_range< Char > CharRange( Char c )
{
    return boost::irange( c, static_cast< Char >( c + 1 ));
}


//
// Predicates
//

Bool Contains( const std::string& s, Char c )
{
    return boost::algorithm::contains( s, CharRange( c ));
}


Bool StartsWith( const std::string& s, Char c )
{
    return boost::algorithm::starts_with( s, CharRange( c ));
}


Bool EndsWith( const std::string& s, Char c )
{
    return boost::algorithm::ends_with( s, CharRange( c ));
}


Bool StartsWith( const std::string& input, const std::string& test )
{
    return boost::algorithm::starts_with( input, test );
}


Bool EndsWith( const std::string& input, const std::string& test )
{
    return boost::algorithm::ends_with( input, test );
}


Bool CainStartsWith( const std::string& input, const std::string& test )
{
    return boost::algorithm::istarts_with( input, test );
}


Bool CainEquals( const std::string& input, const std::string& test )
{
    return boost::algorithm::iequals( input, test );
}


//
// Extractors
//

std::string BeforeFirst( const std::string& s, Char c )
{
    auto range = boost::algorithm::find_first( s, CharRange( c ));
    return std::string( s.begin(), range.begin() );
}


std::string AfterFirst( const std::string& s, Char c )
{
    auto range = boost::algorithm::find_first( s, CharRange( c ));
    return range.empty() ? std::string()
                         : std::string( range.begin() + 1, s.end() );
}


//
// Manipulators
//

void Trim( std::string& s )
{
    boost::algorithm::trim( s );
}


std::string TrimCopy( const std::string& s )
{
    return boost::algorithm::trim_copy( s );
}


//
// Concatenation
//

std::string Join( const std::vector< std::string >& sequence, const std::string& separator )
{
    return boost::algorithm::join( sequence, separator );
}


///////////////////////////////////////////////////////////////////////////////
//
// ToString
//

std::string ToString( Bool x )
{
    return x ? "true" : "false";
}


//
// Integers
//

template< typename T >
std::string IntegerToString( T x )
{
    std::stringstream ss;
    ss << std::dec << x;
    return ss.str();
}

std::string ToString( Int16 x )  { return IntegerToString( x ); }
std::string ToString( Uint16 x ) { return IntegerToString( x ); }
std::string ToString( Int32 x )  { return IntegerToString( x ); }
std::string ToString( Uint32 x ) { return IntegerToString( x ); }
std::string ToString( Long x )   { return IntegerToString( x ); }
std::string ToString( Ulong x )  { return IntegerToString( x ); }
std::string ToString( Int64 x )  { return IntegerToString( x ); }
std::string ToString( Uint64 x ) { return IntegerToString( x ); }


//
// Floatings
//

template< typename T >
std::string FloatingToString( T x )
{
    std::stringstream ss;
    ss << x;
    return ss.str();
}

std::string ToString( Float  x ) { return FloatingToString( x ); } 
std::string ToString( Double x ) { return FloatingToString( x ); }


///////////////////////////////////////////////////////////////////////////////
//
// To String <Type>
//

template<> std::string ToStringT< Bool >()   { return "Bool"; }
template<> std::string ToStringT< Char >()   { return "Char"; }
template<> std::string ToStringT< Byte >()   { return "Byte"; }
template<> std::string ToStringT< Int16 >()  { return "Int16"; }
template<> std::string ToStringT< Uint16 >() { return "Uint16"; }
template<> std::string ToStringT< Int32 >()  { return "Int32"; }
template<> std::string ToStringT< Uint32 >() { return "Uint32"; }
template<> std::string ToStringT< Long >()   { return "Long"; }
template<> std::string ToStringT< Ulong >()  { return "Ulong"; }
template<> std::string ToStringT< Int64 >()  { return "Int64"; }
template<> std::string ToStringT< Uint64 >() { return "Uint64"; }

template<> std::string ToStringT< Float >()  { return "Float"; }
template<> std::string ToStringT< Double >() { return "Double"; }


///////////////////////////////////////////////////////////////////////////////
//
// Formatter
//

namespace Detail
{

Formatter::Formatter( const std::string& format )   
    : m_impl( new Formatter::Impl( format ))
{}


std::string Formatter::GetString() const
{
    return m_impl->GetString();
}


//
// Feeding Arguments
//

void Formatter::Feed( Int value )
{
    m_impl->Distribute( [=] ( const std::string& ) -> std::string
    {
        return ToString( value );
    });
}


void Formatter::Feed( Uint value )
{
    m_impl->Distribute( [=] ( const std::string& ) -> std::string
    {
        return ToString( value );
    });
}


void Formatter::Feed( Int64 value )
{
    m_impl->Distribute( [=] ( const std::string& ) -> std::string
    {
        return ToString( value );
    });
}


void Formatter::Feed( Uint64 value )
{
    m_impl->Distribute( [=] ( const std::string& ) -> std::string
    {
        return ToString( value );
    });
}


void Formatter::Feed( Long value )
{
    m_impl->Distribute( [=] ( const std::string& ) -> std::string
    {
        return ToString( value );
    });
}


void Formatter::Feed( Ulong value )
{
    m_impl->Distribute( [=] ( const std::string& ) -> std::string
    {
        return ToString( value );
    });
}


void Formatter::Feed( Float value )
{
    m_impl->Distribute( [=] ( const std::string& ) -> std::string
    {
        return ToString( value );
    });
}


void Formatter::Feed( Double value )
{
    m_impl->Distribute( [=] ( const std::string& ) -> std::string
    {
        return ToString( value );
    });
}


void Formatter::Feed( const std::string& value )
{
    m_impl->Distribute( [=] ( const std::string& ) -> std::string
    {
        return value;
    });
}


//
// Implementation
//

Formatter::Impl::Impl( const std::string& format )
{
    std::string buffer = format;
    std::string head = "";

    while ( Contains( buffer, '}' ))
    {
        const std::string piece = BeforeFirst( buffer, '}' );
        buffer = AfterFirst( buffer, '}' );

        if ( ! Contains( piece, '{' ))
        {
            head += piece + "}";
            continue;
        }
        
        head += BeforeFirst( piece, '{' );

        const std::string sindex = AfterFirst( piece, '{' );
        Lexical::Integer< Uint > index;
        
        if ( ! index.TryParse( sindex ))
        {
            continue;
        }

        FormatItem item;
        item.argIndex = index;
        item.head = head;
        head.clear();
        
        m_items.push_back( item );
    }

    if ( m_items.empty() )
    {
        m_tail = format;
    }
    else
    {
        m_tail = buffer;
    }
}


void Formatter::Impl::Distribute(
    std::function< std::string ( const std::string& ) > formatResolver )
{
    const Uint index = m_feedingIndex ++;

    for ( auto& item : m_items )
    {
        if ( index != item.argIndex ) { continue; }

        item.content = formatResolver( "" );  // TODO: Item format may be specified in format string.
    }
}


std::string Formatter::Impl::GetString() const
{
    std::ostringstream stream;

    for ( const auto& item : m_items )
    {
        stream << item.head << item.content;
    }

    stream << m_tail;

    return stream.str();
}


} // namespace Detail

///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
