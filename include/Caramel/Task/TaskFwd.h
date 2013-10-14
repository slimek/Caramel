// Caramel C++ Library - Task Facility - Forwards Header

#ifndef __CARAMEL_TASK_TASK_FWD_H
#define __CARAMEL_TASK_TASK_FWD_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <functional>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Typedefs
//

typedef std::function< void() > TaskFunction;


///////////////////////////////////////////////////////////////////////////////
//
// Forwards Declaration
//

class Task;
class TaskExecutor;
class TaskPoller;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_FWD_H
