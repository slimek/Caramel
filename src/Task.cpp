// Caramel C++ Library - Task Facility Implementation

#include "CaramelPch.h"

#include "Task/PooledThread.h"
#include "Task/TaskImpl.h"
#include "Task/TaskPollerImpl.h"
#include "Task/ThreadPoolImpl.h"
#include "Task/WorkerThreadImpl.h"
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Chrono/TimedBool.h>
#include <Caramel/Error/CatchException.h>
#include <Caramel/String/Format.h>
#include <Caramel/Task/StdAsync.h>
#include <Caramel/Thread/ThisThread.h>
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
//   PooledThread
//   ThreadPool
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


TaskCore::CatchResult TaskCore::Catch() const
{
    CARAMEL_CHECK( m_impl->IsValid() );
    return m_impl->Catch();
}


//
// Cancel the Task
//

Bool TaskCore::Cancel()
{
    CARAMEL_CHECK( m_impl->IsValid() );
    return m_impl->Cancel();
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

Bool TaskCore::IsFaulted()  const { return m_impl->m_state == TASK_STATE_FAULTED; }
Bool TaskCore::IsCanceled() const { return m_impl->m_state == TASK_STATE_CANCELED; }

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

        if ( m_state == TASK_STATE_CANCELED )
        {
            return;
        }

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


TaskCore::CatchResult TaskImpl::Catch() const
{
    this->DoWait();

    TaskCore::CatchResult result;
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


Bool TaskImpl::Cancel()
{
    LockGuard lock( m_stateMutex );

    if ( m_state < TASK_STATE_RUNNING )
    {
        m_state = TASK_STATE_CANCELED;
        return true;
    }

    return false;
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
    : m_impl( new TaskPollerImpl( this, MakeClockProxy< TickClock >() ))
{
}


TaskPoller::TaskPoller( const ClockProxy& clock )
    : m_impl( new TaskPollerImpl( this, clock ))
{
}


void TaskPoller::Submit( TaskCore& task )
{
    if ( task.HasDelay() )
    {
        task.StartDelay( *this );
        m_impl->AddDelayTask( task );
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

TaskPollerImpl::TaskPollerImpl( TaskPoller* host, const ClockProxy& clock )
    : m_host( host )
    , m_clock( clock )
{
}


void TaskPollerImpl::AddDelayTask( const TaskCore& task )
{
    const Ticks dueTime = m_clock.SinceEpoch() + task.GetDelayDuration();
    m_delayedTasks.Push( dueTime, task );
}


void TaskPollerImpl::PollFor( const Ticks& sliceTicks )
{
    while ( ! m_delayedTasks.IsEmpty() )
    {
        Ticks dueTime;
        m_delayedTasks.PeekTopKey( dueTime );

        if ( m_clock.SinceEpoch() < dueTime ) { break; }

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
// Pooled Thread
//

PooledThread::PooledThread( ThreadPoolImpl* threadPool, Uint index )
    : m_threadPool( threadPool )
    , m_stopped( false )
{
    m_name = Format( "{0}[{1}]", threadPool->GetName(), index );

    m_thread.reset( new Thread( m_name, [=] { this->Execute(); } ));
}


void PooledThread::Wake( TaskCore& task )
{
    LockGuard lock( m_mutex );

    CARAMEL_ASSERT( ! m_runningTask.IsValid() );

    m_runningTask = task;
    m_waken.notify_one();
}


void PooledThread::StopAndJoin()
{
    CARAMEL_ASSERT( ! m_stopped );

    m_stopped = true;
    m_waken.notify_one();
    m_thread->Join();
}


void PooledThread::Execute()
{
    for ( ;; )
    {
        if ( m_stopped ) { break; }

        UniqueLock ulock( m_mutex );

        if ( m_runningTask.IsValid() )
        {
            TaskCore task;
            std::swap( task, m_runningTask );

            task.Run();

            ulock.unlock();

            m_threadPool->AddReadyThread( this );
        }
        else
        {
            m_waken.wait( ulock );
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Thread Pool
//

ThreadPool::ThreadPool( const std::string& name, Uint numThreads )
    : m_impl( new ThreadPoolImpl( name, numThreads, this ))
{
}


ThreadPool::~ThreadPool()
{
}


void ThreadPool::Submit( TaskCore& task )
{
    if ( task.HasDelay() )
    {
        CARAMEL_THROW( "ThreadPool doesn't support delay yet, task: %s", task.Name() );
    }
    else
    {
        m_impl->AddReadyTask( task );
    }
}


void ThreadPool::AddReadyTask( TaskCore& task )
{
    m_impl->AddReadyTask( task );
}


void ThreadPool::Shutdown()
{
    m_impl->Shutdown();
}


//
// Implementation
//

ThreadPoolImpl::ThreadPoolImpl( const std::string& name, Uint numThreads, ThreadPool* host )
    : m_name( name )
    , m_host( host )
    , m_shutdown( false )
{
    m_threads.reserve( numThreads );

    for ( Uint i = 0; i < numThreads; ++ i )
    {
        m_threads.push_back( new PooledThread( this, i ));
        m_readyThreads.Push( &m_threads[i] );
    }
}


ThreadPoolImpl::~ThreadPoolImpl()
{
    if ( ! m_shutdown )
    {
        CARAMEL_TRACE_WARN_HERE( "Destroy the thread pool %s before shutdown it", m_name );

        // REMARKS: Do not rely on the destructor to shutdown a thread pool.
        //          Here is only a remedy.

        this->Shutdown();
    }
}


void ThreadPoolImpl::Shutdown()
{
    CARAMEL_ASSERT( ! m_shutdown );

    m_shutdown = true;

    while ( m_readyThreads.Size() != m_threads.size() || ! m_readyTasks.IsEmpty() )
    {
        ThisThread::SleepFor( Ticks( 100 ));
    }

    for ( Uint i = 0; i < m_threads.size(); ++ i )
    {
        m_threads[i].StopAndJoin();
    }
}


void ThreadPoolImpl::AddReadyTask( TaskCore& task )
{
    task.BecomeReady( *m_host );

    if ( m_readyTasks.IsEmpty() )
    {
        PooledThread* thread = nullptr;
        if ( m_readyThreads.TryPop( thread ))
        {
            thread->Wake( task );
            return;
        }
    }

    m_readyTasks.Push( task );

    if ( ! m_readyThreads.IsEmpty() )
    {
        this->TryDispatchOneTask();
    }
}


void ThreadPoolImpl::AddReadyThread( PooledThread* thread )
{
    TaskCore task;
    if ( m_readyTasks.TryPop( task ))
    {
        thread->Wake( task );
        return;
    }

    m_readyThreads.Push( thread );

    if ( ! m_readyTasks.IsEmpty() )
    {
        this->TryDispatchOneTask();
    }
}


void ThreadPoolImpl::TryDispatchOneTask()
{
    PooledThread* thread = nullptr;
    if ( m_readyThreads.TryPop( thread ))
    {
        TaskCore task;
        if ( m_readyTasks.TryPop( task ))
        {
            thread->Wake( task );
            return;
        }
        else
        {
            m_readyThreads.Push( thread );
        }
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
    task.BecomeReady( *this );

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
