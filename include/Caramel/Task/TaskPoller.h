// Caramel C++ Library - Task Facility - Task Poller Header

#ifndef __CARAMEL_TASK_TASK_POLLER_H
#define __CARAMEL_TASK_TASK_POLLER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Chrono/ClockProxy.h>
#include <Caramel/Chrono/TickClock.h>
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
    explicit TaskPoller( const ClockProxy& clock );

    void Submit( TaskCore& task ) override;

    using TaskExecutor::Submit;
    
    void PollOne();

    //
    // Poll at least one task.
    // Then poll tasks until empty, or slice ticks timeout.
    //
    void PollFor( const Ticks& sliceTicks );


private:

    void AddReadyTask( TaskCore& task ) override;

    std::shared_ptr< TaskPollerImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_POLLER_H
