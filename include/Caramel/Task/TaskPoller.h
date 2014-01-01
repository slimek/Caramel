// Caramel C++ Library - Task Facility - Task Poller Header

#ifndef __CARAMEL_TASK_TASK_POLLER_H
#define __CARAMEL_TASK_TASK_POLLER_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Task/Detail/TaskFwd.h>
#include <Caramel/Task/TaskExecutor.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Poller
//

class TaskPollerImpl;

class TaskPoller : public TaskExecutor
{
public:

    TaskPoller();

    void Submit( Task& task ) override;

    void PollOne();

    //
    // Poll at least one task.
    // Then poll tasks until empty, or slice ticks timeout.
    //
    void PollFor( const Ticks& sliceTicks );


private:

    void AddTaskToReady( Task& task ) override;

    std::shared_ptr< TaskPollerImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_POLLER_H
