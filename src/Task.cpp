// Caramel C++ Library - Task Facility Implementation

#include "CaramelPch.h"

#include "Task/StrandImpl.h"
#include "Task/TaskImpl.h"
#include "Task/TaskPollerImpl.h"
#include "Task/WorkerThreadImpl.h"
#include <Caramel/Async/TimedBool.h>
#include <Caramel/Chrono/TickClock.h>


namespace Caramel
{

//
// Contents
//
//   Task
//   Strand
//   TaskPoller
//   WorkerThread
//

///////////////////////////////////////////////////////////////////////////////
//
// Task
//

Task::Task()
    : m_impl( new TaskImpl )
{
    m_impl->m_host = this;
}


Task::Task( const std::string& name, TaskFunction&& f )
    : m_impl( new TaskImpl( name, std::move( f )))
{
    m_impl->m_host = this;
}


Task& Task::DelayFor( const Ticks& duration )
{
    CARAMEL_CHECK( m_impl->IsValid() );

    m_impl->DelayFor( duration );
    return *this;
}


Task& Task::Schedule( Strand& strand )
{
    CARAMEL_CHECK( m_impl->IsValid() );

    m_impl->Schedule( strand.m_impl );
    return *this;
}


//
// Internal Functions - Call by TaskExecutor
//

void Task::StartDelay( TaskExecutor& executor )
{
}


void Task::PushToStrand( TaskExecutor& executor )
{
    CARAMEL_CHECK( m_impl->IsValid() );

    m_impl->PushToStrand( &executor );
}


void Task::Run()
{
    CARAMEL_CHECK( m_impl->IsValid() );

    m_impl->Run();
}


//
// Properties
//

Bool Task::IsValid() const { return m_impl->IsValid(); }

std::string Task::Name() const { return m_impl->m_name; }

Bool  Task::HasDelay()         const { return m_impl->m_hasDelay; }
Ticks Task::GetDelayDuration() const { return m_impl->m_delayDuration; }

Bool Task::HasStrand() const { return m_impl->m_strand; }


//
// Implementation
//

TaskImpl::TaskImpl()
    : m_name( "Not-a-task" )
    , m_hasDelay( false )
    , m_executor( nullptr )
{
}


TaskImpl::TaskImpl( const std::string& name, TaskFunction&& f )
    : m_name( name )
    , m_function( f )
    , m_hasDelay( false )
    , m_executor( nullptr )
{
}


void TaskImpl::DelayFor( const Ticks& duration )
{
    CARAMEL_ASSERT( ! m_hasDelay );

    m_delayDuration = duration;
    m_hasDelay = true;
}


void TaskImpl::Schedule( const StrandPtr& strand )
{
    CARAMEL_ASSERT( ! m_strand );

    m_strand = strand;
}


void TaskImpl::PushToStrand( TaskExecutor* executor )
{
    CARAMEL_ASSERT(( ! m_executor ) || m_executor == executor );
    CARAMEL_ASSERT( m_strand );

    m_executor = executor;

    m_strand->PushTask( this->shared_from_this() );

    TaskPtr readyTask;
    if ( m_strand->PeekFrontIfReady( readyTask ))
    {
        readyTask->m_executor->AddReadyTask( *readyTask->GetHost() );
    }
}


void TaskImpl::Run()
{
    m_function();

    if ( m_strand )
    {
        m_strand->PopFront( this->shared_from_this() );

        TaskPtr readyTask;
        if ( m_strand->PeekFrontIfReady( readyTask ))
        {
            m_executor->AddReadyTask( *readyTask->GetHost() );
        }
    }
}


//
// State Transition
//

Bool TaskImpl::TransitToDelayed()
{
    return true;
}


Bool TaskImpl::TransitToBlocked()
{
    return true;
}


Bool TaskImpl::TransitToReady()
{
    return true;
}


///////////////////////////////////////////////////////////////////////////////
//
// Strand
//

void Strand::CancelAll()
{
}


//
// Implementation
//

void StrandImpl::PushTask( const TaskPtr& task )
{
    auto ulock = UniqueLock( m_queueMutex );

    CARAMEL_VERIFY( task->TransitToBlocked() );

    m_blockedTasks.push_back( task );
}


Bool StrandImpl::PeekFrontIfReady( TaskPtr& task )
{
    auto ulock = UniqueLock( m_queueMutex );

    if ( m_blockedTasks.empty() ) { return false; }

    TaskPtr frontTask = m_blockedTasks.front();

    if ( frontTask->TransitToReady() )
    {
        task = frontTask;
        return true;
    }

    return false;
}


void StrandImpl::PopFront( const TaskPtr& callingTask )
{
    auto ulock = UniqueLock( m_queueMutex );

    CARAMEL_ASSERT( m_blockedTasks.front() == callingTask );
    m_blockedTasks.pop_front();
}


///////////////////////////////////////////////////////////////////////////////
//
// TaskPoller
//

TaskPoller::TaskPoller()
{
    m_impl = std::make_shared< TaskPollerImpl >( this );
}


void TaskPoller::Submit( Task& task )
{
    if ( task.HasDelay() )
    {
        const TickPoint dueTime = TickClock::Now() + task.GetDelayDuration();
        m_impl->m_delayedTasks.Push( dueTime, task );
    }
    else if ( task.HasStrand() )
    {
        task.PushToStrand( *this );
    }
    else
    {
        this->AddReadyTask( task );
    }
}


void TaskPoller::AddReadyTask( Task& task )
{
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

        Task task;
        m_delayedTasks.TryPop( task );

        if ( task.HasStrand() )
        {
            task.PushToStrand( *m_host );
        }
        else
        {
            m_readyTasks.Push( task );
        }
    }

    TimedBool< TickClock > sliceTimeout( sliceTicks );

    Task task;

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


void WorkerThread::Submit( Task& task )
{
    if ( task.HasDelay() )
    {
    }
    else if ( task.HasStrand() )
    {
        CARAMEL_NOT_IMPLEMENTED();
    }
    else
    {
        this->AddReadyTask( task );
    }
}


void WorkerThread::AddReadyTask( Task& task )
{
}


//
// Implementation
//

WorkerThreadImpl::WorkerThreadImpl( const std::string& name, WorkerThread* host )
    : m_name( name )
    , m_host( host )
    , m_stopped( false )
{
    m_thread.reset( new Thread( "Worker:" + name, [=] { this->Execute(); } ) );
}


void WorkerThreadImpl::Execute()
{
    for ( ;; )
    {

    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
