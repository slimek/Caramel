// Caramel C++ Library - Task Facility Implementation

#include "CaramelPch.h"

#include "Task/StrandImpl.h"
#include "Task/TaskImpl.h"
#include "Task/TaskPollerImpl.h"
#include <Caramel/Async/TimedBool.h>
#include <Caramel/Chrono/SteadyClock.h>


namespace Caramel
{

//
// Contents
//
//   Task
//   Strand
//   TaskPoller
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


void Task::Enqueue( TaskExecutor& executor )
{
    CARAMEL_CHECK( m_impl->IsValid() );

    m_impl->Enqueue( &executor );
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


void TaskImpl::Enqueue( TaskExecutor* executor )
{
    CARAMEL_ASSERT( ! m_executor );

    m_executor = executor;

    if ( m_strand )
    {
        m_strand->PushTask( this->shared_from_this() );

        TaskPtr readyTask;
        if ( m_strand->PeekFrontIsReady( readyTask ))
        {
            m_executor->AddTaskToReady( *readyTask->GetHost() );
        }
    }
    else
    {
        m_executor->AddTaskToReady( *m_host );
    }
}


void TaskImpl::Run()
{
    m_function();

    if ( m_strand )
    {
        m_strand->PopFront( this->shared_from_this() );

        TaskPtr readyTask;
        if ( m_strand->PeekFrontIsReady( readyTask ))
        {
            m_executor->AddTaskToReady( *readyTask->GetHost() );
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


Bool StrandImpl::PeekFrontIsReady( TaskPtr& task )
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
    else
    {
        task.Enqueue( *this );
    }
}


void TaskPoller::AddTaskToReady( Task& task )
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

        Task readyTask;
        m_delayedTasks.TryPop( readyTask );
        readyTask.Enqueue( *m_host );
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

} // namespace Caramel
