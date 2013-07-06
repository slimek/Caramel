// Caramel C++ Library - I/O Facility - Input Stream Header

#ifndef __CARAMEL_IO_INPUT_STREAM_H
#define __CARAMEL_IO_INPUT_STREAM_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Input Stream
// - Interface
//

struct InputStream
{
    virtual ~InputStream() {}

    // Returns how many bytes read.
    virtual Uint Read( Void* buffer, Uint size ) = 0;

    // Move read position from current, forwards or backwards.
    virtual void Seek( Int offset ) = 0;

    // Returns the current read position.
    virtual Uint Tell() const = 0;

    // Returns true if this stream has read over the end.
    virtual Bool IsEof() const = 0;


    //
    // Combination Functions
    //

    //
    // Peek
    // - See a few data at the stream, but don't move the read position.
    //   Returns how many bytes actually peeked.
    //
    virtual Uint Peek( Void* buffer, Uint size );

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline Uint InputStream::Peek( Void* buffer, Uint size )
{
    const Uint count = this->Read( buffer, size );
    this->Seek( - static_cast< Int >( count ));
    return count;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_INPUT_STREAM_H
