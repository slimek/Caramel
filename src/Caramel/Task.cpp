// Caramel C++ Library - Task Facility Implementation

#include <Caramel/CaramelPch.h>

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
        m_impl->m_delayedTasks.Push( task->GetDelayDuration(), task );
    }
    else
    {
        m_impl->m_readyTasks.Push( task );
    }
}


void TaskPoller::PollOne()
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
