// Caramel C++ Library - Task Facility - Task Private Header

#ifndef __CARAMEL_TASK_TASK_IMPL_H
#define __CARAMEL_TASK_TASK_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Concurrent/Queue.h>
#include <Caramel/Task/Task.h>


namespace Caramel
{

typedef Detail::TaskHolder TaskHolder;

///////////////////////////////////////////////////////////////////////////////
//
// Task
//

class TaskImpl;
typedef std::shared_ptr< TaskImpl > TaskPtr;

class TaskImpl
{
    friend class TaskCore;

    enum State : Int;
    
public:

    TaskImpl();  // Not-a-task

    TaskImpl( const std::string& name, std::unique_ptr< TaskHolder >&& holder );


    /// Operations ///

    void AddContinuation( TaskPtr continuation );

    void DelayFor( const Ticks& duration );
    void Run();


    /// State Transition ///

    Bool TransitFromTo( State fromState, State toState );


    /// Properties ///

    Bool IsValid() const { return static_cast< Bool >( m_holder ); }  // *1

    // NOTES:
    // 1 - In Android NDK r9b, std::shared_prt can't convert to Bool implicitly.


private:

    std::string m_name;
    std::shared_ptr< TaskHolder > m_holder;


    /// State ///

    enum State : Int
    {
        TASK_S_INITIAL          = 0x01,
        TASK_S_DELAYING         = 0x02,
        TASK_S_WAITING          = 0x04,
        TASK_S_READY            = 0x08,
        TASK_S_RUNNING          = 0x10,
        TASK_S_CANCELED         = 0x20,
        TASK_S_FAULTED          = 0x40,
        TASK_S_RAN_TO_COMPLETE  = 0x80,
    
    } m_state;

    std::mutex m_stateMutex;

    
    /// Delay ///

    Bool  m_hasDelay;
    Ticks m_delayDuration;


    /// Schedule and Run ///

    TaskExecutor* m_executor;


    /// Continuation ///

    typedef Concurrent::Queue< TaskPtr > TaskQueue;
    TaskQueue m_continuations;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_IMPL_H
