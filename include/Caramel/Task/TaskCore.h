// Caramel C++ Library - Task Facility - Task Core Header

#ifndef __CARAMEL_TASK_TASK_CORE_H
#define __CARAMEL_TASK_TASK_CORE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Error/ExceptionPtr.h>
#include <Caramel/Task/Detail/TaskFwd.h>
#include <Caramel/Task/Detail/TaskHolders.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Core
//

class TaskImpl;
enum TaskState : Int;

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

    // Wait until done. Throws exception if faulted.
    void Wait() const;

    // Wait until done. If faulted, you can examine the exception in its result.
    struct CatchResult;
    CatchResult Catch() const;

    
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


//
// Task State
//

enum TaskState : Int
{
    TASK_STATE_UNDEF        = 0,

    TASK_STATE_INITIAL      = 0x01,
    TASK_STATE_DELAYING     = 0x02,
    TASK_STATE_STRANDING    = 0x04,
    TASK_STATE_READY        = 0x08,
    TASK_STATE_RUNNING      = 0x10,

    // Done states
    TASK_STATE_CANCELED     = 0x20,
    TASK_STATE_FAULTED      = 0x40,
    TASK_STATE_RAN_TO_COMP  = 0x80,  // Ran to Completion
};


//
// Task Catch Result
//

struct TaskCore::CatchResult
{
    CatchResult()
        : doneState( TASK_STATE_UNDEF )
    {}

    TaskState doneState;

    AnyFailurePtr anyFailure;
    ExceptionPtr  exception;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_CORE_H
