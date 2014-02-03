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


    /// Setup Task Scheduling ///

    // This task waits due time before scheduling
    Task& DelayFor( const Ticks& ticks );


    /// Properties ///

    Bool IsValid() const;  // Returns false if "Not a task"

    std::string Name() const;

    Bool IsCompleted() const;  // "Ran to Completion" or Cancelled

    // Delay
    Bool  HasDelay()         const;
    Ticks GetDelayDuration() const;


    //
    // Post-Submit Functions
    // - This function should only be called by TaskExecutor
    //

    void StartDelay( TaskExecutor& te );

    void Run();


private:

    std::shared_ptr< TaskImpl > m_impl;
};


//
// Make Task
// - Helper function to make an anonymous task object
//

inline Task MakeTask( const std::string& name, TaskFunction&& f )
{
    return Task( name, std::move( f ));
}


} // namespace Caramel

///////////////////////////////////////////////////////////////////////////////
//
// Macros
//

//
// Task of Bind
// - 1. Make the task function of std::bind.
//   2. Use the function name as the task name.
//

#define CARAMEL_TASK_OF_BIND( function, ... ) \
    Caramel::MakeTask( #function, std::bind( &function, ##__VA_ARGS__ ))


///////////////////////////////////////////////////////////////////////////////

#endif // __CARAMEL_TASK_TASK_H
