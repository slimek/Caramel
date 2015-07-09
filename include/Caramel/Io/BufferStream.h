// Caramel C++ Library - I/O Facility - Buffer Stream Header

#ifndef __CARAMEL_IO_BUFFER_STREAM_H
#define __CARAMEL_IO_BUFFER_STREAM_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Io/InputStream.h>
#include <Caramel/Io/OutputStream.h>
#include <sstream>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Buffer Stream
// - An auto-grow memory stream, based on std::stringstream.
//
//   Usually is used by the step:
//     1. Feed data to the buffer.
//     2. Count the written length of the buffer.
//     3. Allocate a resource large enough to hold the whole data.
//     4. Retrieve data from the buffer to the resource.
//

class BufferStream : public InputStream
                   , public OutputStream
{
public:


    // Position to write / How many bytes have been written.
    Usize Position() const;


    /// Implements OutputStream

    void Write( const Void* data, Usize size ) override;


    /// Implements InputStream

    Usize Read( Void* buffer, Usize size ) override;

    Uint Tell() const override;

    Bool IsEof() const override { return m_eof; }

    // Throws exceptions :
    // - BufferStream doesn't support seeking.
    void Seek( Int offset ) override;


private:
    
    std::stringstream m_stream;
    Bool m_eof { false };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_BUFFER_STREAM_H
