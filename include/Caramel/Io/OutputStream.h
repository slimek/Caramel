// Caramel C++ Library - I/O Facility - Output Stream Header

#ifndef __CARAMEL_IO_OUTPUT_STREAM_H
#define __CARAMEL_IO_OUTPUT_STREAM_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Output Stream 
// - Interface
//

struct OutputStream
{
    virtual ~OutputStream() {}

    virtual void Write( const Void* buffer, Usize size ) = 0;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_OUTPUT_STREAM_H
