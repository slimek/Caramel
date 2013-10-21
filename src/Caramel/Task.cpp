// Caramel C++ Library - Task Facility Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Chrono/SteadyClock.h>
#include <Caramel/Task/TaskImpl.h>
#include <Caramel/Task/TaskPollerImpl.h>


namespace Caramel
{

//
// Contents
//
//   Task
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
    if ( ! m_impl->m_delayedTasks.IsEmpty() )
    {
        TickPoint dueTime;
        m_impl->m_delayedTasks.PeekTopKey( dueTime );

        if ( dueTime < TickClock::Now() )
        {
            TaskPtr readyTask;
            m_impl->m_delayedTasks.TryPop( readyTask );
            m_impl->m_readyTasks.Push( readyTask );
        }
    }

    TaskPtr task;

    if ( m_impl->m_readyTasks.TryPop( task ))
    {
        task->Run();
        return;
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
