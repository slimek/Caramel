// Caramel C++ Library - Task Facility - Task Core Header

#ifndef __CARAMEL_TASK_TASK_CORE_H
#define __CARAMEL_TASK_TASK_CORE_H
#pragma once

#include <Caramel/Caramel.h>
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

    Bool IsCompleted() const;  // "Ran to Completion" or Cancelled

    // Delay
    Bool  HasDelay()         const;
    Ticks GetDelayDuration() const;

    //
    // Post-Submit Functions
    // - These functions should only be called by TaskExecutor
    //

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
