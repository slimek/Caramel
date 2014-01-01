// Caramel C++ Library - Task Facility - Task Poller Private Header

#ifndef __CARAMEL_TASK_TASK_POLLER_IMPL_H
#define __CARAMEL_TASK_TASK_POLLER_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
#include "Task/TaskImpl.h"
#include <Caramel/Concurrent/PriorityQueue.h>
#include <Caramel/Concurrent/Queue.h>
#include <Caramel/Task/TaskPoller.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Poller
//

class TaskPollerImpl
{
    friend class TaskPoller;

private:

    typedef Concurrent::PriorityQueue< TickPoint, Task > DelayedTaskQueue;
    DelayedTaskQueue m_delayedTasks;

    typedef Concurrent::Queue< Task > ReadyTaskQueue;
    ReadyTaskQueue m_readyTasks;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_POLLER_IMPL_H
