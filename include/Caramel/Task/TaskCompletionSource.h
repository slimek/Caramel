// Caramel C++ Library - Task Facility - Task Completion Source Header

#ifndef __CARAMEL_TASK_TASK_COMPLETION_SOURCE_H
#define __CARAMEL_TASK_TASK_COMPLETION_SOURCE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Task/Task.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Completion Source
//

template< typename Result >
class TaskCompletionSource
{
public:

    typedef Result ResultType;

    TaskCompletionSource();

    Task< Result > GetTask() const { return m_task; }

    void SetResult( Result value );

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

    void Set();

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
inline void TaskCompletionSource< Result >::SetResult( Result result )
{
    // NOTES: Here is a little hack that Task.Run() should only be called
    //        by a TaskExecutor :p

    // TODO: Maybe the m_task will need BecomeReady() before Run().
    //       In this case we can make a dummy TaskExecutor here.

    *m_result = result;
    m_task.Run();
}


//
// Tasks return no values
//

inline TaskCompletionSource< void >::TaskCompletionSource()
    : m_task( [] {} )
{
}


inline void TaskCompletionSource< void >::Set()
{
    // NOTES: Here is a little hack that Task.Run() should only be called
    //        by a TaskExecutor :p

    // TODO: Maybe the m_task will need BecomeReady() before Run().
    //       In this case we can make a dummy TaskExecutor here.

    m_task.Run();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_COMPLETION_SOURCE_H
