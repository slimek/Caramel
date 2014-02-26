// Caramel C++ Library - Task Facility - Task Private Header

#ifndef __CARAMEL_TASK_TASK_IMPL_H
#define __CARAMEL_TASK_TASK_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Concurrent/Queue.h>
#include <Caramel/Task/Task.h>
#include <condition_variable>


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

    ~TaskImpl();


    /// Operations ///

    void SetExecutor( TaskExecutor& executor );

    void AddContinuation( TaskPtr continuation );

    void DelayFor( const Ticks& duration );
    void Run();

    void Wait() const;


    /// State Transition ///

    Bool TransitFromTo( State fromState, State toState );


    /// Properties ///

    Bool IsValid() const { return static_cast< Bool >( m_holder ); }  // *1
    Bool IsDone()  const { return TASK_S_RUNNING < m_state; }

    // NOTES:
    // 1 - In Android NDK r9b, std::shared_prt can't convert to Bool implicitly.


private:

    void NotifyDone();


    /// Data Members ///

    std::string m_name;
    std::shared_ptr< TaskHolder > m_holder;


    /// State ///

    enum State : Int
    {
        TASK_S_UNDEF        = 0,

        TASK_S_INITIAL      = 0x01,
        TASK_S_DELAYING     = 0x02,
        TASK_S_WAITING      = 0x04,
        TASK_S_READY        = 0x08,
        TASK_S_RUNNING      = 0x10,

        // Done states
        TASK_S_CANCELED     = 0x20,
        TASK_S_FAULTED      = 0x40,
        TASK_S_RAN_TO_COMP  = 0x80, // Ran to Completion
    
    } m_state;

    mutable std::mutex m_stateMutex;
    mutable std::condition_variable m_becomesDone;

    
    /// Delay ///

    Bool  m_hasDelay;
    Ticks m_delayDuration;


    /// Schedule and Run ///

    TaskExecutor* m_executor;


    /// Continuation ///

    typedef Concurrent::QueueWithSnapshot< TaskPtr > TaskQueue;
    TaskQueue m_continuations;

    std::exception_ptr m_exception;
    mutable Bool m_exceptionRethrown;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_IMPL_H
