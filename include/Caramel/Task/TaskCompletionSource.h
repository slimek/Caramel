// Caramel C++ Library - Task Facility - Task Completion Source Header

#ifndef __CARAMEL_TASK_TASK_COMPLETION_SOURCE_H
#define __CARAMEL_TASK_TASK_COMPLETION_SOURCE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Task/StdAsync.h>
#include <Caramel/Task/Task.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Completion Source
// - The class name comes from .NET Task Parallel Library.
//

template< typename Result >
class TaskCompletionSource
{
public:

    typedef Result ResultType;

    TaskCompletionSource();

    Task< Result > GetTask() const { return m_task; }

    void RunTask( Result result, TaskExecutor& executor );

    // Run the task and all its continuations with StdAsync.
    void RunTask( Result result );

private:

    std::shared_ptr< Result > m_result;
    Task< Result > m_task;
};


//
// Tasks return no values
//

template<>
class TaskCompletionSource< void >
{
public:
    
    TaskCompletionSource();

    Task< void > GetTask() const { return m_task; }

    void RunTask( TaskExecutor& executor );

    // Run the task and all its continuations with StdAsync.
    void RunTask();

private:

    Task< void > m_task;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Result >
inline TaskCompletionSource< Result >::TaskCompletionSource()
    : m_result( std::make_shared< Result >() )
    , m_task( [=] { return *m_result; } )
{
}


template< typename Result >
inline void TaskCompletionSource< Result >::RunTask( Result result, TaskExecutor& executor )
{
    *m_result = result;
    executor.Submit( m_task );
}


template< typename Result >
inline void TaskCompletionSource< Result >::RunTask( Result result )
{
    *m_result = result;
    StdAsync::Submit( m_task );
}


//
// Tasks return no values
//

inline TaskCompletionSource< void >::TaskCompletionSource()
    : m_task( [] {} )
{
}


inline void TaskCompletionSource< void >::RunTask( TaskExecutor& executor )
{
    executor.Submit( m_task );
}


inline void TaskCompletionSource< void >::RunTask()
{
    StdAsync::Submit( m_task );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_COMPLETION_SOURCE_H
