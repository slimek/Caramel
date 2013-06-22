// Caramel C++ Library - String Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/String/Sprintf.h>
#include <Caramel/String/SprintfManager.h>
#include <Caramel/String/Utf8String.h>


namespace Caramel
{

//
// Contents
//
// 1. Sprintf
// 2. SprintfBuffer
// 3. SprintfManager
// 4. Utf8String
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
    //SprintfBuffer* buffer = SprintfManager::Instance()->AllocateBuffer();

    CARAMEL_NOT_IMPLEMENTED();  
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
    m_chunk = new Char[ CHUNK_SIZE ];
    
    // Align buffer acoording to the cache lines
    void* p = m_chunk;
    std::size_t space = 0;
    std::align( BUFFER_ALIGN, SIZE, p, space );  
    m_buffer = reinterpret_cast< Char* >( p );

    CARAMEL_ASSERT( m_buffer + SIZE + sizeof( Uint32 ) <= m_chunk + CHUNK_SIZE );

    // Padding before head
    std::fill( m_chunk, m_buffer, PAD_CHAR );

    // Padding after tail
    std::fill( m_buffer + SIZE, m_chunk + CHUNK_SIZE, PAD_CHAR );

    // Put the tail guard
    m_tailGuard = reinterpret_cast< Uint32* >( m_buffer + SIZE );
    *m_tailGuard = TAIL_GUARD;

    this->Clear();
}


SprintfBuffer::~SprintfBuffer()
{
    delete[] m_chunk;
}


void SprintfBuffer::Clear()
{
    std::fill( m_buffer, m_buffer + SIZE, 0 );
}


///////////////////////////////////////////////////////////////////////////////
//
// Sprintf Manager
//
// - CAUTION: Sprintf utility is the foundation of Exception and Trace macros.
//            Don't use these macros in Sprintf code.
//

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

Utf8String::Utf8String( const std::string& u8Text )
    : Inherited( u8Text )
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

    this->assign( u8Text );
    return true;
}


Bool Utf8String::TryParse( const Byte* data, Uint length )
{
    CARAMEL_NOT_IMPLEMENTED();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel