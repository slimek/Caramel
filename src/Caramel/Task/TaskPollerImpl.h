// Caramel C++ Library - Task Facility - Task Poller Private Header

#ifndef __CARAMEL_TASK_TASK_POLLER_IMPL_H
#define __CARAMEL_TASK_TASK_POLLER_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Concurrent/PriorityQueue.h>
#include <Caramel/Concurrent/Queue.h>
#include <Caramel/Task/TaskImpl.h>
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

    typedef Concurrent::PriorityQueue< TickDuration, TaskPtr > DelayedTaskQueue;
    DelayedTaskQueue m_delayedTasks;

    typedef Concurrent::Queue< TaskPtr > ReadyTaskQueue;
    ReadyTaskQueue m_readyTasks;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_POLLER_IMPL_H
