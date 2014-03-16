// Caramel C++ Library - Task Facility - Task Poller Private Header

#ifndef __CARAMEL_TASK_TASK_POLLER_IMPL_H
#define __CARAMEL_TASK_TASK_POLLER_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
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

public:

    explicit TaskPollerImpl( TaskPoller* host );

    //
    // Scheduling - Process in order:
    // - 1. Delaying tasks
    //   2. Put tasks into the ready queue
    //

    /// Run Tasks ///

    void PollFor( const Ticks& sliceTicks );


private:

    TaskPoller* m_host;

    typedef Concurrent::PriorityQueue< TickPoint, TaskCore > DelayedTaskQueue;
    DelayedTaskQueue m_delayedTasks;

    typedef Concurrent::Queue< TaskCore > ReadyTaskQueue;
    ReadyTaskQueue m_readyTasks;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_POLLER_IMPL_H
