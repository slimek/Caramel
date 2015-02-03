// Caramel C++ Library - I/O Facility - Input Memory Stream Header

#ifndef __CARAMEL_IO_INPUT_MEMORY_STREAM_H
#define __CARAMEL_IO_INPUT_MEMORY_STREAM_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Io/InputStream.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Input Memory Stream
//

class InputMemoryStream : public InputStream
{
public:
    
    explicit InputMemoryStream( const Void* buffer, Uint length );

    template< typename T, Uint n >
    explicit InputMemoryStream( const T(& buffer)[n] );

    // Specialized for C-style string
    // - Will discard all the trailing '\0'
    template< Uint n >
    explicit InputMemoryStream( const Char(& sz)[n] );


    Uint Length() const { return m_length; }


    /// Implements InputStream ///

    Uint Read( Void* buffer, Uint size ) override;

    void Seek( Int offset ) override;

    Uint Tell() const override { return m_position; }

    Bool IsEof() const override { return m_position == m_length; }


private:

    const Byte* m_buffer { nullptr };
    Uint m_length { 0 };
    Uint m_position { 0 };
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T, Uint n >
inline InputMemoryStream::InputMemoryStream( const T(& buffer)[n] )
    : m_buffer( reinterpret_cast< const Byte* >( &buffer[0] ))
    , m_length( n )
{}


//
// Specialization for C-style string
//
// - When a user write the following code:
//
//     InputMemoryStream stream( "Alice" );
//
//   He/she may think the stream length is 5, but in fact the C-style string "Alice"
//   has 6 bytes in memory, including the trailing '\0'
//
//   In this case, we decide to discard all the trailing '\0',
//   since the stream length to be 5 is more intuitive.
//
template< Uint n >
inline InputMemoryStream::InputMemoryStream( const Char(& sz)[n] )
    : m_buffer( reinterpret_cast< const Byte* >( &sz[0] ))
    , m_length( n )
{
    // Discard all trailing '\0'
    // - A C-style string always has one '\0'.
    while ( sz[ m_length - 1 ] == '\0' ) { -- m_length; }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_INPUT_MEMORY_STREAM_H
