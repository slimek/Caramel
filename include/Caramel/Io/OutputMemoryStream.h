// Caramel C++ Library - I/O Facility - Output Memory Stream Header

#ifndef __CARAMEL_IO_OUTPUT_MEMORY_STREAM_H
#define __CARAMEL_IO_OUTPUT_MEMORY_STREAM_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Io/OutputStream.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Output Memory Stream
// - Provides a stream interface on a FIXED size memory block.
//

class OutputMemoryStream : public OutputStream
{
public:

    OutputMemoryStream( Void* buffer, Usize length );


    /// Properties ///

    Usize Length() const { return m_length; }
    
    // Position to write / How many bytes have been written.
    Usize Position() const { return m_position; }



    /// Implements OutputStream ///

    // Throws if write out of the stream.
    void Write( const Void* data, Usize size ) override;


private:

    Byte* m_buffer { nullptr };
    Usize m_length { 0 };
    Usize m_position { 0 };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_OUTPUT_MEMORY_STREAM_H
