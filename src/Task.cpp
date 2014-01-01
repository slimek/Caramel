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
}


Task::Task( const std::string& name, TaskFunction&& f )
    : m_impl( new TaskImpl( name, std::move( f )))
{
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
{
}


TaskImpl::TaskImpl( const std::string& name, TaskFunction&& f )
    : m_name( name )
    , m_function( f )
    , m_hasDelay( false )
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


void TaskImpl::Run()
{
    m_function();
}


///////////////////////////////////////////////////////////////////////////////
//
// Strand
//

void Strand::CancelAll()
{
}


///////////////////////////////////////////////////////////////////////////////
//
// TaskPoller
//

TaskPoller::TaskPoller()
    : m_impl( new TaskPollerImpl )
{
}


void TaskPoller::Submit( const Task& task )
{
    if ( task.HasDelay() )
    {
        const TickPoint dueTime = TickClock::Now() + task.GetDelayDuration();
        m_impl->m_delayedTasks.Push( dueTime, task );
    }
    else
    {
        m_impl->m_readyTasks.Push( task );
    }
}


void TaskPoller::PollOne()
{
    this->PollFor( Ticks::Zero() );
}


void TaskPoller::PollFor( const Ticks& sliceTicks )
{
    while ( ! m_impl->m_delayedTasks.IsEmpty() )
    {
        TickPoint dueTime;
        m_impl->m_delayedTasks.PeekTopKey( dueTime );

        if ( TickClock::Now() < dueTime ) { break; }

        Task readyTask;
        m_impl->m_delayedTasks.TryPop( readyTask );
        m_impl->m_readyTasks.Push( readyTask );
    }

    TimedBool< TickClock > sliceTimeout( sliceTicks );

    Task task;

    while ( m_impl->m_readyTasks.TryPop( task ))
    {
        task.Run();

        if ( sliceTimeout ) { break; }
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
