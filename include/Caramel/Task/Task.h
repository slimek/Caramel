// Caramel C++ Library - Task Facility - Task Header

#ifndef __CARAMEL_TASK_TASK_H
#define __CARAMEL_TASK_TASK_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Task/Detail/TaskFwd.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task
//

class TaskImpl;

class Task
{
public:

    Task();  // Create a "not-a-task". Submit it results in exception.

    Task( const std::string& name, TaskFunction&& f );


    //
    // Setup Task Scheduling
    //
    //   Delay    : The task waits due time before scheduling.
    //   Schedule : The task depends on a strand and would run in order.
    //

    Task& DelayFor( const Ticks& ticks );
    Task& Schedule( Strand& strand );


    /// Properties ///

    Bool IsValid() const;  // Returns false if "Not a task"

    std::string Name() const;

    Bool IsCompleted() const;  // "Ran to Completion" or Cancelled

    // Delay
    Bool  HasDelay()         const;
    Ticks GetDelayDuration() const;

    // Schedule
    Bool HasStrand() const;


    //
    // Post-Submit Functions
    // - This function should only be called by TaskExecutor
    //

    void StartDelay( TaskExecutor& te );

    // Push this task into strand queue.
    void PushToStrand( TaskExecutor& te );

    void Run();


private:

    std::shared_ptr< TaskImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_H
