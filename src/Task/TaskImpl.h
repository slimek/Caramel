// Caramel C++ Library - Task Facility - Task Private Header

#ifndef __CARAMEL_TASK_TASK_IMPL_H
#define __CARAMEL_TASK_TASK_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Concurrent/Queue.h>
#include <Caramel/Error/ExceptionPtr.h>
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

public:

    TaskImpl();  // Not-a-task

    // NOTES: the name may be an empty string if not given at the higher functions.
    TaskImpl( std::string&& name, std::unique_ptr< TaskHolder >&& holder );

    ~TaskImpl();


    /// Operations ///

    void SetExecutor( TaskExecutor& executor );

    void AddContinuation( TaskPtr continuation );

    void DelayFor( const Ticks& duration );
    void Run();

    void Wait() const;
    
    TaskCore::CatchResult Catch() const;

    Bool Cancel();


    /// State Transition ///

    Bool TransitFromTo( TaskState fromState, TaskState toState );


    /// Properties ///

    Bool IsValid() const { return static_cast< Bool >( m_holder ); }  // *1
    Bool IsDone()  const { return TASK_STATE_RUNNING < m_state; }

    // NOTES:
    // 1 - In Android NDK r9b, std::shared_prt can't convert to Bool implicitly.


private:

    void NotifyDone();

    void DoWait() const;


    /// Data Members ///

    std::string m_name;
    std::shared_ptr< TaskHolder > m_holder;


    /// State ///

    TaskState m_state;

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

    ExceptionPtr m_exception;
    mutable Bool m_exceptionHandled;
    
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_IMPL_H
