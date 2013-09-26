// Caramel C++ Library - Task Facility - Task Types Header

#ifndef __CARAMEL_TASK_TASK_TYPES_H
#define __CARAMEL_TASK_TASK_TYPES_H

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
class Workpile;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_TYPES_H
