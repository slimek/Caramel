// Caramel C++ Library - Task Facility - Detail - Forwards Header

#ifndef __CARAMEL_TASK_DETAIL_TASK_FWD_H
#define __CARAMEL_TASK_DETAIL_TASK_FWD_H
#pragma once

#include <Caramel/Caramel.h>
#include <functional>


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

template< typename Result >
class BasicTask;

}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_DETAIL_TASK_FWD_H
