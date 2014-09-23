// Caramel C++ Library - Task Facility - Task Timer Header

#ifndef __CARAMEL_TASK_TASK_TIMER_H
#define __CARAMEL_TASK_TASK_TIMER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Task/TaskFwd.h>
#include <functional>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Timer
// - This is a periodic timer based on Task facility.
//   If you want a deadline timer, use Task.SetDelay().
//

class TaskTimerImpl;

class TaskTimer
{
public:

    typedef std::function< void() > WorkFunction;


    /// Creation ///

    TaskTimer() {}  // Create a "not-a-timer".

    TaskTimer(
        const std::string& name, TaskExecutor& executor, const Ticks& period, WorkFunction f );

    // NOTES: The TaskExecutor should support Delay function.
    //        Currently only TaskPoller and WorkerThread are available.

    ~TaskTimer();


    /// Operations ///

    // Throws an exception if there is one timer working.
    void Start(
        const std::string& name, TaskExecutor& executor, const Ticks& period, WorkFunction f );

    // If there is no timer working, do nothing.
    void Cancel();


private:

    std::shared_ptr< TaskTimerImpl > m_impl;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_TIMER_H
