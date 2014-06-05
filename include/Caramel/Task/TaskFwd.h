// Caramel C++ Library - Task Facility - Forwards Header

#ifndef __CARAMEL_TASK_TASK_FWD_H
#define __CARAMEL_TASK_TASK_FWD_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Forwards Declaration
//

class TaskExecutor;
class TaskPoller;
class WorkerThread;

class TaskCore;

template< typename Result >
class Task;

namespace Detail
{

class TaskHolder;

}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_FWD_H
