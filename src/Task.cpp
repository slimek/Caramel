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

Task::Task( const std::string& name, TaskFunction&& f )
    : m_impl( new TaskImpl( name, std::move( f )))
{
}


Task& Task::DelayFor( const Ticks& duration )
{
    m_impl->DelayFor( duration );
    return *this;
}


Task& Task::Schedule( Strand& strand )
{
    return *this;
}


//
// Implementation
//

TaskImpl::TaskImpl( const std::string& name, TaskFunction&& f )
    : m_name( name )
    , m_function( f )
    , m_delayed( false )
{
}


void TaskImpl::DelayFor( const Ticks& duration )
{
    CARAMEL_ASSERT( ! m_delayed );

    m_delayDuration = duration;
    m_delayed = true;
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


void TaskPoller::Submit( const Task& inputTask )
{
    TaskPtr task = inputTask.GetImpl();

    if ( task->IsDelayed() )
    {
        const TickPoint dueTime = TickClock::Now() + task->GetDelayDuration();

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

        TaskPtr readyTask;
        m_impl->m_delayedTasks.TryPop( readyTask );
        m_impl->m_readyTasks.Push( readyTask );
    }

    TimedBool< TickClock > sliceTimeout( sliceTicks );

    TaskPtr task;

    while ( m_impl->m_readyTasks.TryPop( task ))
    {
        task->Run();

        if ( sliceTimeout ) { break; }
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
