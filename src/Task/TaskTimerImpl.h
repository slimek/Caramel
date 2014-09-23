// Caramel C++ Library - Task Facility - Task Timer Private Header

#ifndef __CARAMEL_TASK_TASK_TIMER_IMPL_H
#define __CARAMEL_TASK_TASK_TIMER_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Task/TaskTimer.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Timer
//

class TaskTimerImpl : public std::enable_shared_from_this< TaskTimerImpl >
{
    typedef TaskTimer::WorkFunction WorkFunction;

public:

    TaskTimerImpl(
        const std::string& name, TaskExecutor& executor, const Ticks& period );

    std::string Name() const { return m_name; }

    void MakeAndSubmitTask( WorkFunction f );

    void Cancel();

private:

    std::string m_name;
    TaskExecutor* m_executor { nullptr };
    Ticks m_period;

    Bool m_canceled { false };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_TIMER_IMPL_H
