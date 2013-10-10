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


//
// Implementation
//

TaskImpl::TaskImpl( const std::string& name, TaskFunction&& f )
    : m_name( name )
    , m_function( f )
{
}


Bool TaskImpl::IsDelayed() const
{
    return false;
}


TickDuration TaskImpl::GetDelayDuration() const
{
    return TickDuration();
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
        //const TickTimePoint dueTicks = TickClock::Now() + task->GetDelayDuration();

        m_impl->m_delayedTasks.Push( task->GetDelayDuration(), task );
    }
    else
    {
        m_impl->m_readyTasks.Push( task );
    }
}


void TaskPoller::PollOne()
{
    TaskPtr task;

    if ( m_impl->m_readyTasks.TryPop( task ))
    {
        // Invoke the task
        return;
    }

    if ( m_impl->m_delayedTasks.IsEmpty() ) { return; }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
