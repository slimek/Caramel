// Caramel C++ Library - Task Facility Implementation

#include "CaramelPch.h"

#include "Task/TaskImpl.h"
#include "Task/TaskPollerImpl.h"
#include "Task/WorkerThreadImpl.h"
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Chrono/TimedBool.h>
#include <Caramel/Error/CatchException.h>
#include <Caramel/String/Format.h>
#include <Caramel/Task/StdAsync.h>
#include <algorithm>
#include <future>


namespace Caramel
{

//
// Contents
//
//   Task
//   TaskPoller
//   WorkerThread
//   StdAsync
//

///////////////////////////////////////////////////////////////////////////////
//
// Task
//

TaskCore::TaskCore()
    : m_impl( new TaskImpl )
{
}


TaskCore::TaskCore( const std::string& name, std::unique_ptr< TaskHolder >&& holder )
    : m_impl( new TaskImpl( name, std::move( holder )))
{
}


TaskCore::TaskCore( const std::shared_ptr< TaskImpl >& impl )
    : m_impl( impl )
{
}


//
// Setup the Task
//

void TaskCore::AddContinuation( TaskCore& continuation )
{
    CARAMEL_CHECK( m_impl->IsValid() );
    m_impl->AddContinuation( continuation.m_impl );
}


void TaskCore::DoDelayFor( const Ticks& duration )
{
    CARAMEL_CHECK( m_impl->IsValid() );
    m_impl->DelayFor( duration );
}


//
// Wait for Task to Complete
//

void TaskCore::Wait() const
{
    CARAMEL_CHECK( m_impl->IsValid() );
    m_impl->Wait();
}


TaskCore::WaitOrCatchResult TaskCore::WaitOrCatch() const
{
    CARAMEL_CHECK( m_impl->IsValid() );
    return m_impl->WaitOrCatch();
}



//
// Internal Functions - Call by TaskExecutor
//


Bool TaskCore::StartDelay( TaskExecutor& executor )
{
    CARAMEL_CHECK( m_impl->IsValid() );
    m_impl->SetExecutor( executor );
    return true;
}


Bool TaskCore::StartWait( TaskExecutor& executor )
{
    CARAMEL_CHECK( m_impl->IsValid() );
    m_impl->SetExecutor( executor );
    return true;
}


Bool TaskCore::BecomeReady( TaskExecutor& executor )
{
    CARAMEL_CHECK( m_impl->IsValid() );
    m_impl->SetExecutor( executor );
    return true;
}


void TaskCore::Run()
{
    CARAMEL_CHECK( m_impl->IsValid() );
    m_impl->Run();
}


//
// Properties
//

Bool TaskCore::IsValid() const { return m_impl->IsValid(); }
Bool TaskCore::IsDone()  const { return m_impl->IsDone(); }

Bool TaskCore::IsFaulted() const { return TASK_STATE_FAULTED == m_impl->m_state; }

std::string TaskCore::Name() const { return m_impl->m_name; }

Bool  TaskCore::HasDelay()         const { return m_impl->m_hasDelay; }
Ticks TaskCore::GetDelayDuration() const { return m_impl->m_delayDuration; }

const TaskHolder* TaskCore::GetHolder() const { return m_impl->m_holder.get(); }


//
// Implementation
//

TaskImpl::TaskImpl()
    : m_name( "Not-a-task" )
    , m_state( TASK_STATE_INITIAL )
    , m_hasDelay( false )
    , m_executor( nullptr )
    , m_exceptionHandled( false )
{
}


TaskImpl::TaskImpl( const std::string& name, std::unique_ptr< TaskHolder >&& holder )
    : m_name( name )
    , m_holder( std::move( holder ))
    , m_state( TASK_STATE_INITIAL )
    , m_hasDelay( false )
    , m_executor( nullptr )
    , m_exceptionHandled( false )
{
}


TaskImpl::~TaskImpl()
{
    // Trace the exception if it isn't rethrown.

    if ( m_exception && ! m_exceptionHandled )
    {
        CARAMEL_TRACE_WARN( "Task %s throws:\n%s", m_name, m_exception.TracingMessage() );
    }
}


//
// Operations
//

void TaskImpl::SetExecutor( TaskExecutor& executor )
{
    CARAMEL_ASSERT( nullptr == m_executor || &executor == m_executor );
    m_executor = &executor;
}


void TaskImpl::AddContinuation( TaskPtr continuation )
{
    Bool canSubmit = false;

    {
        LockGuard lock( m_stateMutex );

        if ( this->IsDone() )
        {
            canSubmit = true;
        }
        else
        {
            m_continuations.Push( continuation );
        }
    }

    if ( canSubmit )
    {
        m_executor->Submit( TaskCore( continuation ));
    }
}


void TaskImpl::DelayFor( const Ticks& duration )
{
    CARAMEL_ASSERT( ! m_hasDelay );

    m_delayDuration = duration;
    m_hasDelay = true;
}


void TaskImpl::Run()
{
    {
        LockGuard lock( m_stateMutex );
        m_state = TASK_STATE_RUNNING;
    }

    auto xc = CatchException( [=] { m_holder->Invoke(); } );

    TaskQueue::Snapshot continuations;

    {
        LockGuard lock( m_stateMutex );

        if ( xc )
        {
            m_exception = xc.Exception();
            m_state = TASK_STATE_FAULTED;
        }
        else
        {
            m_state = TASK_STATE_RAN_TO_COMP;
        }

        continuations = m_continuations.GetSnapshot();
        m_continuations.Clear();

        this->NotifyDone();
    }

    for ( TaskPtr task : continuations )
    {
        m_executor->Submit( TaskCore( task ));
    }
}


void TaskImpl::Wait() const
{
    this->DoWait();

    if ( m_exception )
    {
        m_exceptionHandled = true;
        m_exception.Rethrow();
    }
}


TaskCore::WaitOrCatchResult TaskImpl::WaitOrCatch() const
{
    this->DoWait();

    TaskCore::WaitOrCatchResult result;
    result.doneState = m_state;

    if ( m_exception )
    {
        result.exception = m_exception;

        // Results in a null if m_exception is not an AnyFailure.
        result.anyFailure = AnyFailurePtr::CastFrom( m_exception );

        m_exceptionHandled = true;
    }

    return result;
}


void TaskImpl::DoWait() const
{
    UniqueLock ulock( m_stateMutex );

    while ( ! this->IsDone() )
    {
        m_becomesDone.wait( ulock );
    }
}


//
// State Transition
// - TODO: Not complete yet.
//

Bool TaskImpl::TransitFromTo( TaskState fromState, TaskState toState )
{
    LockGuard lock( m_stateMutex );

    if ( fromState == m_state )
    {
        m_state = toState;
        return true;
    }
    else
        return false;
}


void TaskImpl::NotifyDone()
{
    m_becomesDone.notify_all();    
}


///////////////////////////////////////////////////////////////////////////////
//
// TaskPoller
//

TaskPoller::TaskPoller()
{
    m_impl = std::make_shared< TaskPollerImpl >( this );
}


void TaskPoller::Submit( TaskCore& task )
{
    if ( task.HasDelay() )
    {
        task.StartDelay( *this );

        const TickPoint dueTime = TickClock::Now() + task.GetDelayDuration();
        m_impl->m_delayedTasks.Push( dueTime, task );
    }
    else
    {
        this->AddReadyTask( task );
    }
}


void TaskPoller::AddReadyTask( TaskCore& task )
{
    task.BecomeReady( *this );
    m_impl->m_readyTasks.Push( task );
}


void TaskPoller::PollOne()
{
    m_impl->PollFor( Ticks::Zero() );
}


void TaskPoller::PollFor( const Ticks& sliceTicks )
{
    m_impl->PollFor( sliceTicks );
}


//
// Implementation
//

TaskPollerImpl::TaskPollerImpl( TaskPoller* host )
    : m_host( host )
{
}


void TaskPollerImpl::PollFor( const Ticks& sliceTicks )
{
    while ( ! m_delayedTasks.IsEmpty() )
    {
        TickPoint dueTime;
        m_delayedTasks.PeekTopKey( dueTime );

        if ( TickClock::Now() < dueTime ) { break; }

        TaskCore task;
        m_delayedTasks.TryPop( task );
        m_readyTasks.Push( task );
    }

    TimedBool< TickClock > sliceTimeout( sliceTicks );

    TaskCore task;

    while ( m_readyTasks.TryPop( task ))
    {
        task.Run();

        if ( sliceTimeout ) { break; }
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Worker Thread
//

WorkerThread::WorkerThread( const std::string& name )
{
    m_impl = std::make_shared< WorkerThreadImpl >( name, this );
}


WorkerThread::~WorkerThread()
{
    if ( !m_impl->m_stopped )
    {
        CARAMEL_ALERT( "WorkerThread[%s] not stopped before destroyed", m_impl->m_name );
        
        m_impl->m_stopped = true;
        m_impl->m_readyTasks.Complete();
        m_impl->m_thread->Detach();
    }
}


void WorkerThread::Submit( TaskCore& task )
{
    if ( task.HasDelay() )
    {
        task.StartDelay( *this );

        auto lastDueTime = TickPoint::MaxValue();
        m_impl->m_delayTasks.PeekTopKey( lastDueTime );

        const TickPoint dueTime = TickClock::Now() + task.GetDelayDuration();
        m_impl->m_delayTasks.Push( dueTime, task );

        if ( dueTime < lastDueTime )
        {
            // Force to recalculate the next deley duration.
            // See WorkerThreadImpl::Execute().
            m_impl->m_readyTasks.PulseAll();
        }
    }
    else
    {
        this->AddReadyTask( task );
    }
}


void WorkerThread::Stop()
{
    m_impl->m_stopped = true;
    m_impl->m_readyTasks.Complete();
    m_impl->m_thread->Join();
}


void WorkerThread::AddReadyTask( TaskCore& task )
{
    task.BecomeReady( *this );
    m_impl->m_readyTasks.Push( task );
}


//
// Implementation
//

WorkerThreadImpl::WorkerThreadImpl( const std::string& name, WorkerThread* host )
    : m_name( name )
    , m_host( host )
    , m_stopped( false )
{
    m_thread.reset( new Thread( Format( "Worker[{0}]", name ), [=] { this->Execute(); } ) );
}


void WorkerThreadImpl::Execute()
{
    const auto maxDelay = Ticks( 10000 );  // 10 seconds

    for ( ;; )
    {
        if ( m_stopped ) { break; }

        // Step 1 : Move all expired delay works to ready queue

        const TickPoint now = TickClock::Now();
        auto nextDelay = maxDelay;

        TickPoint dueTime;
        while ( m_delayTasks.PeekTopKey( dueTime ))
        {
            if ( now < dueTime )
            {
                nextDelay = std::min( maxDelay, Ticks( dueTime - now ));
                break;
            }

            TaskCore exTask;  // expired task

            CARAMEL_VERIFY( m_delayTasks.TryPop( exTask ));
            m_readyTasks.Push( exTask );
        }


        // Step 2 : Run the task or wait

        TaskCore task;
        if ( m_readyTasks.PopOrWaitFor( task, nextDelay ))
        {
            task.Run();
        }
    }


    // Check unprocessed tasks before stopping this worker.

    if ( ! m_delayTasks.IsEmpty() && ! m_readyTasks.IsEmpty() )
    {
        CARAMEL_TRACE_WARN( "WorkerThread[%s] discards some tasks" );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Std Async
//

#if !defined( CARAMEL_SYSTEM_IS_ANDROID )

void StdAsync::Submit( TaskCore& task )
{
    if ( task.HasDelay() )
    {
        CARAMEL_THROW( "StdAsync doesn't support delay, task: %s", task.Name() );
    }
    else
    {
        this->AddReadyTask( task );
    }
}


void StdAsync::AddReadyTask( TaskCore& task )
{
    std::async( std::launch::async,
    [task]
    {
        // task is a const variable and can't call Run().
        TaskCore copy = task;
        copy.Run();
    });
}

#else

// NOTES: Until Android NDK r9b, std::future and std::async are not supported.

void StdAsync::Submit( TaskCore& task )
{
    CARAMEL_NOT_IMPLEMENTED();
}


void StdAsync::AddReadyTask( TaskCore& task )
{
    CARAMEL_NOT_IMPLEMENTED();
}

#endif // !CARAMEL_SYSTEM_IS_ANDROID


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
