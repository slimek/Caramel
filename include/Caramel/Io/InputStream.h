// Caramel C++ Library - I/O Amenity - Input Stream Header

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

    // returns true if this stream has read over the end.
    virtual Bool IsEof() const = 0;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_INPUT_STREAM_H
