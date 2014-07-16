// Caramel C++ Library - Task Facility - When All Header

#ifndef __CARAMEL_TASK_WHEN_ALL_H
#define __CARAMEL_TASK_WHEN_ALL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Error/Exception.h>
#include <Caramel/Task/Task.h>
#include <atomic>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Composition Task - When All
//
// Run after all tasks are complete.
// - If one of the tasks canceled, When-All task will never be run.
//   If one of the tasks faulted, When-All task will run at once. The input task is faulted.
//
//   Usage:
//
//   std::vector< Task< void > > tasks = ... // Build tasks
//  
//   WhenAll( "tasks completed", tasks,
//   [] ( const Task< void >& task )
//   {
//       // Do something when all tasks completed, or any task faulted.
//   });
//

template< typename TaskSequence, typename Function >
inline void WhenAll( const std::string& name, const TaskSequence& tasks, Function f );


///////////////////////////////////////////////////////////////////////////////
//
// When All Wrapper
//

template< typename Function >
class WhenAllWrapper : public std::enable_shared_from_this< WhenAllWrapper< Function >>
{
public:
    
    WhenAllWrapper( const std::string& name, Function&& f, Uint numTasks );

    void CompleteOne( const Task< void >& task );

private:

    std::string m_name;
    Function m_function;

    Uint m_numTasks;
    std::atomic< Uint > m_completeCount;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename TaskSequence, typename Function >
inline void WhenAll( const std::string& name, const TaskSequence& tasks, Function f )
{
    const Uint numTasks = static_cast< Uint >( tasks.size() );

    if ( numTasks == 0 )
    {
        CARAMEL_THROW( "WhenAll() needs at least one task" );
    }

    auto whenAllWrapper =
        std::make_shared< WhenAllWrapper< Function > >( name, std::move( f ), numTasks );

    for ( auto task : tasks )
    {
        task.Then(
        [=] ( const Task< void >& t )
        {
            whenAllWrapper->CompleteOne( t );
        });
    }
}


template< typename Function >
inline WhenAllWrapper< Function >::WhenAllWrapper(
    const std::string& name, Function&& f, Uint numTasks
)
    : m_name( name )
    , m_function( std::move( f ))
    , m_numTasks( numTasks )
    , m_completeCount( 0 )
{
}


template< typename Function >
inline void WhenAllWrapper< Function >::CompleteOne( const Task< void >& t )
{
    t.Catch();  // Sink the exceptions.

    if ( t.IsFaulted()
      || m_numTasks == ++ m_completeCount )
    {
        auto thiz = this->shared_from_this();

        // Make a non-const copy to continue another task.
        Task< void > taskCopy = t;

        taskCopy.Then( m_name,
        [=] ( const Task< void >& task )
        {
            thiz->m_function( task );
        });
    }
}
    

///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_WHEN_ALL_H
