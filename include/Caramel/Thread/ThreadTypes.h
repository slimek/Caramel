// Caramel C++ Library - Thread Facility - Thread Types Header

#ifndef __CARAMEL_THREAD_THREAD_TYPES_H
#define __CARAMEL_THREAD_THREAD_TYPES_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <functional>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Common Types
//

typedef std::function< void() > WorkFunction;


///////////////////////////////////////////////////////////////////////////////
//
// Forwards Declaration
//

class ThisThread;
class Thread;
class ThreadId;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_THREAD_TYPES_H
