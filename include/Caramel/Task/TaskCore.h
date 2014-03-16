// Caramel C++ Library - Task Facility - Task Core Header

#ifndef __CARAMEL_TASK_TASK_CORE_H
#define __CARAMEL_TASK_TASK_CORE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Task/Detail/TaskFwd.h>
#include <Caramel/Task/Detail/TaskHolders.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Core
//

class TaskImpl;

class TaskCore
{
    friend class TaskImpl;

public:

    TaskCore();


    /// Properties ///

    Bool IsValid() const;  // Returns false if "Not a task"

    std::string Name() const;

    Bool IsFaulted() const;
    Bool IsDone()    const;  // "Ran to Completion", Faulted or Canceled


    /// Operations ///

    // Delay
    Bool  HasDelay()         const;
    Ticks GetDelayDuration() const;

    void Wait() const;  // Wait until done.

    
    //
    // Post-Submit Functions
    // - These functions should only be called by TaskExecutor
    //

    // State transition
    // - If these functions return false, the executor should discard this task.
    Bool StartDelay ( TaskExecutor& executor );
    Bool StartWait  ( TaskExecutor& executor );
    Bool BecomeReady( TaskExecutor& executor );
    
    void Run();


protected:

    TaskCore( const std::string& name, std::unique_ptr< Detail::TaskHolder >&& holder );
    TaskCore( const std::shared_ptr< TaskImpl >& impl );

    void AddContinuation( TaskCore& continuation );

    void DoDelayFor( const Ticks& duration );

    const Detail::TaskHolder* GetHolder() const;


    std::shared_ptr< TaskImpl > m_impl;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_CORE_H
