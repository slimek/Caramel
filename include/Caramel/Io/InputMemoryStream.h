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


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_INPUT_MEMORY_STREAM_H
