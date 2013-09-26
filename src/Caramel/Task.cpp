// Caramel C++ Library - Task Facility Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Task/TaskImpl.h>
#include <Caramel/Task/WorkpileImpl.h>


namespace Caramel
{

//
// Contents
//
//   Task
//   Workpile
//

///////////////////////////////////////////////////////////////////////////////
//
// Task
//

Task::Task( TaskFunction&& f )
    : m_impl( new TaskImpl( std::move( f )))
{
}


//
// Implementation
//

TaskImpl::TaskImpl( TaskFunction&& f )
    : m_function( f )
{
}


///////////////////////////////////////////////////////////////////////////////
//
// Workpile
//

Workpile::Workpile()
    : m_impl( new WorkpileImpl )
{
}


void Workpile::Submit( const Task& task )
{
    m_impl->m_delayedTasks.Push( 1, task );
}


void Workpile::PollOne()
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
