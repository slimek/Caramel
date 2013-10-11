// Caramel C++ Library - Task Facility - Task Header

#ifndef __CARAMEL_TASK_TASK_H
#define __CARAMEL_TASK_TASK_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Task/TaskFwd.h>


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

    Task();  // Create a "not-a-task". Submit it results in nothing.

    Task( const std::string& name, TaskFunction&& f );


    /// Delay : Schedule the task after due time. ///

    Task& DelayFor( const TickDuration& ticks );


    /// Properties ///

    std::string Name() const;

    Bool IsEmpty()     const;  // "Not a task"
    Bool IsCompleted() const;  // "Ran to Completion" or Cancelled


    /// Internal Accessors ///
    
    std::shared_ptr< TaskImpl > GetImpl() const { return m_impl; }


private:

    std::shared_ptr< TaskImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_H
