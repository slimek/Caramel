// Caramel C++ Library - Task Facility Implementation

#include "CaramelPch.h"

#include "Task/PooledThread.h"
#include "Task/StdAsyncImpl.h"
#include "Task/TaskImpl.h"
#include "Task/TaskPollerImpl.h"
#include "Task/TaskTimerImpl.h"
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
//   TaskTimer
//   TaskPoller
//   WorkerThread
//   PooledThread
//   ThreadPool
//   StdAsync
//   StdAsyncCenter
//

///////////////////////////////////////////////////////////////////////////////
//
// Task
//

TaskCore::TaskCore()
    : m_impl( new TaskImpl )
{
}


TaskCore::TaskCore( std::string&& name, std::unique_ptr< TaskHolder >&& holder )
    : m_impl( new TaskImpl( std::move( name ), std::move( holder )))
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


std::string TaskCore::MakeDefaultThenTaskName() const
{
    // NOTES: If the current task's name is empty,
    //        its meaningless to give the then task a name of "-Then".

    CARAMEL_CHECK( m_impl->IsValid() );
    if ( m_impl->m_name.empty() )
    {
        return std::string();
    }
    else
    {
        return m_impl->m_name + "-Then";
    }
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


TaskImpl::TaskImpl( std::string&& name, std::unique_ptr< TaskHolder >&& holder )
    : m_name( std::move( name ))
    , m_holder( std::move( holder ))
    , m_state( TASK_STATE_INITIAL )
    , m_hasDelay( false )
    , m_executor( nullptr )
    , m_exceptionHandled( false )
{
}


TaskImpl::~TaskImpl()
{
    // Alert the exception if it isn't rethrown.

    if ( m_exception && ! m_exceptionHandled )
    {
        CARAMEL_ALERT( "Task[{0}] throws:\n{1}", m_name, m_exception.TracingMessage() );
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
    Bool canceled = false;
    Bool canSubmit = false;

    {
        LockGuard lock( m_stateMutex );

        if ( this->IsCanceled() )
        {
            canceled = true;
        }
        else if ( this->IsDone() )
        {
            canSubmit = true;
        }
        else
        {
            m_continuations.Push( continuation );
        }
    }

    if ( canceled )
    {
        continuation->Cancel();
    }
    else if ( canSubmit )
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

    if ( ! continuations.IsEmpty() )
    {
        TaskCore firstContinue;

        for ( TaskPtr task : continuations )
        {
            if ( m_state == TASK_STATE_FAULTED && ! task->CanContinueWhenFaulted() )
            {
                task->Cancel();
                continue;
            }

            if ( ! firstContinue.IsValid() )
            {
                firstContinue = TaskCore( task );
            }
            else
            {
                m_executor->Submit( TaskCore( task ));
            }
        }

        // The first continuation should run immediately.
        firstContinue.Run();
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
    result.name = m_name;
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
    Bool canceled = false;
    TaskQueue::SnapshotType continuations;

    {
        LockGuard lock( m_stateMutex );

        if ( m_state < TASK_STATE_RUNNING )
        {
            m_state = TASK_STATE_CANCELED;
            canceled = true;
            continuations = m_continuations.GetSnapshot();
            m_becomesDone.notify_all();
        }
    }

    if ( canceled )
    {
        for ( auto cond : continuations )
        {
            cond->Cancel();
        }
    }

    return canceled;
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
// Task Timer
//

TaskTimer::TaskTimer(
    const std::string& name, TaskExecutor& executor, const Ticks& period, WorkFunction f )
    : m_impl( new TaskTimerImpl( name, executor, period ))
{
    // For using shared_from_this(), we wait the shared_ptr created.
    m_impl->MakeAndSubmitTask( f );
}


TaskTimer::~TaskTimer()
{
    if ( m_impl )
    {
        m_impl->Cancel();
    }
}


void TaskTimer::Start(
    const std::string& name, TaskExecutor& executor, const Ticks& period, WorkFunction f )
{
    if ( m_impl )
    {
        CARAMEL_THROW( "TaskTimer[{0}] is working, make new timer[{1}] failed", m_impl->Name(), name );
    }

    m_impl.reset( new TaskTimerImpl( name, executor, period ));
    m_impl->MakeAndSubmitTask( f );
}

void TaskTimer::Cancel()
{
    if ( ! m_impl ) { return; }

    m_impl->Cancel();
}


//
// Implementation
//

TaskTimerImpl::TaskTimerImpl(
    const std::string& name, TaskExecutor& executor, const Ticks& period )
    : m_name( name )
    , m_executor( &executor )
    , m_period( period )
{
}


void TaskTimerImpl::MakeAndSubmitTask( WorkFunction f )
{
    if ( m_canceled ) { return; }

    auto thiz = this->shared_from_this();

    auto task = MakeTask( m_name,
    [=]
    {
        if ( thiz->m_canceled ) { return; }

        auto xc = CatchException( f );
        if ( xc )
        {
            CARAMEL_ALERT( "TaskTimer[{0}] throws:\n{1}", thiz->m_name, xc.TracingMessage() );
        }

        thiz->MakeAndSubmitTask( f );
    });

    task.DelayFor( m_period );

    m_executor->Submit( task );
}


void TaskTimerImpl::Cancel()
{
    m_canceled = true;
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
        CARAMEL_ALERT( "WorkerThread[{0}] not stopped before destroyed", m_impl->m_name );
        
        m_impl->m_stopped = true;
        m_impl->m_readyTasks.Complete();
        m_impl->m_thread->Join();
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
        TraceWarn( "WorkerThread[{0}] discards some tasks", m_name );
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


void PooledThread::Stop()
{
    CARAMEL_ASSERT( ! m_stopped );
    m_stopped = true;
}


void PooledThread::Join()
{
    CARAMEL_ASSERT( m_stopped );
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
        CARAMEL_THROW( "ThreadPool doesn't support delay yet, task: \"{0}\"", task.Name() );
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


Usize ThreadPool::GetNumReadyTasks() const
{
    return m_impl->m_readyTasks.Size();
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
        CARAMEL_ALERT( "Destroy the thread pool {0} before shutdown it", m_name );

        // REMARKS: Do not rely on the destructor to shutdown a thread pool.
        //          Here is only a remedy.

        this->Shutdown();
    }
}


void ThreadPoolImpl::Shutdown()
{
    CARAMEL_ASSERT( ! m_shutdown );

    m_shutdown = true;
    m_readyTasks.Clear();

    // Stop all threads first, then wait them to join.

    for ( auto& pt : m_threads )
    {
        pt.Stop();
    }

    for ( auto& pt : m_threads )
    {
        pt.Join();
    }
}


void ThreadPoolImpl::AddReadyTask( TaskCore& task )
{
    // TODO: AddReadyTask() and Shutdown() should be mutually exclusive...

    if ( m_shutdown )
    {
        TraceWarn( "ThreadPool[{0}] discard Task[{1}]", m_name, task.Name() );
        return;
    }

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

void StdAsync::Submit( TaskCore& task )
{
    StdAsyncCenter::Instance()->Submit( task );
}


void StdAsyncProxy::Submit( TaskCore& task )
{
    StdAsyncCenter::Instance()->Submit( task );
}


void StdAsyncProxy::AddReadyTask( TaskCore& task )
{
    StdAsyncCenter::Instance()->AddReadyTask( task );
}


///////////////////////////////////////////////////////////////////////////////
//
// Std Async Center
//

void StdAsyncCenter::Submit( TaskCore& task )
{
    if ( task.HasDelay() )
    {
        CARAMEL_THROW( "StdAsync doesn't support delay, task: \"{0}\"", task.Name() );
    }

    this->AddReadyTask( task );
}


#if !defined( CARAMEL_SYSTEM_IS_ANDROID )

void StdAsyncCenter::AddReadyTask( TaskCore& task )
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

// NOTES: Until Android NDK r10c, std::future and std::async are not supported.

void StdAsyncCenter::AddReadyTask( TaskCore& task )
{
    task.BecomeReady( *this );

    std::thread thread(
    [task]
    {
        // task is a const variable and can't call Run();
        TaskCore copy = task;
        copy.Run();
    });

    thread.detach();
}

#endif // !CARAMEL_SYSTEM_IS_ANDROID


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
