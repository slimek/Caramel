// Caramel C++ Library - Task Facility - Task Private Header

#ifndef __CARAMEL_TASK_TASK_IMPL_H
#define __CARAMEL_TASK_TASK_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Task/Task.h>


namespace Caramel
{

typedef Detail::TaskHolder TaskHolder;

///////////////////////////////////////////////////////////////////////////////
//
// Task
//

class TaskImpl
{
    friend class TaskCore;

public:

    TaskImpl();  // Not-a-task

    TaskImpl( const std::string& name, TaskHolder* holder );


    /// Operations ///

    void DelayFor( const Ticks& duration );
    void Run();


    /// State Transition ///

    Bool TransitToDelayed();
    Bool TransitToBlocked();
    Bool TransitToReady();


    /// Properties ///

    Bool IsValid() const { return static_cast< Bool >( m_holder ); }  // *1

    // NOTES:
    // 1 - In Android NDK r9b, std::unique_prt can't convert to Bool implicitly.


private:

    std::string m_name;
    std::unique_ptr< TaskHolder > m_holder;


    /// State ///

    enum State
    {
        TASK_S_INITIAL          = 0x01,
        TASK_S_DELAYING         = 0x02,
        TASK_S_WAITING          = 0x04,
        TASK_S_READY            = 0x08,
        TASK_S_RUNNING          = 0x10,
        TASK_S_RAN_TO_COMPLETE  = 0x20,
    
    } m_state;

    std::mutex m_stateMutex;

    
    /// Delay ///

    Bool  m_hasDelay;
    Ticks m_delayDuration;


    /// Schedule and Run ///

    TaskExecutor* m_executor;

};

typedef std::shared_ptr< TaskImpl > TaskPtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_IMPL_H
