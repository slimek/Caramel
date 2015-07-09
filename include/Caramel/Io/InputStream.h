// Caramel C++ Library - I/O Facility - Input Stream Header

#ifndef __CARAMEL_IO_INPUT_STREAM_H
#define __CARAMEL_IO_INPUT_STREAM_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Input Stream
// - Interface ( with some helper functions )
//   The stream size should not exceed 2 G.
//

struct InputStream
{
    virtual ~InputStream() {}

    // Returns how many bytes read.
    virtual Usize Read( Void* buffer, Usize size ) = 0;

    // Move read position from current, forwards or backwards.
    virtual void Seek( Int offset ) = 0;

    // Returns the current read position.
    virtual Uint Tell() const = 0;

    // Returns true if this stream has read OVER the end.
    virtual Bool IsEof() const = 0;


    //
    // Combination Functions
    //

    //
    // Peek
    // - See a few data at the stream, but don't move the read position.
    //   Returns how many bytes actually peeked.
    //
    virtual Usize Peek( Void* buffer, Usize size );


    //
    // Rewind
    // - Move the read position to the beginning of this stream.
    //   Clear all buffers.
    //
    virtual void Rewind();
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline Usize InputStream::Peek( Void* buffer, Usize size )
{
    const Usize count = this->Read( buffer, size );
    this->Seek( - static_cast< Int >( count ));
    return count;
}


inline void InputStream::Rewind()
{
    this->Seek( - static_cast< Int >( this->Tell() ));
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_INPUT_STREAM_H
