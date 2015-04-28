// Caramel C++ Library - Task Facility - Promise Header

#ifndef __CARAMEL_TASK_PROMISE_H
#define __CARAMEL_TASK_PROMISE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Task/StdAsync.h>
#include <Caramel/Task/Task.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Promise
// - The Task/Promise pair work like the std::future/promise.
//
//   Reference:
//     In Visual C++ PPL, it is called task_completion_event.
//     In .NET Framework, it is called Promise.
//

template< typename Result >
class Promise
{
public:

    typedef Result ResultType;

    Promise();
    explicit Promise( std::string taskName );

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
class Promise< void >
{
public:
    
    Promise();
    explicit Promise( std::string taskName );

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
inline Promise< Result >::Promise()
    : m_result( std::make_shared< Result >() )
{
    auto result = m_result;
    m_task = MakeTask( [=] { return *result; });

    // NOTES: DO NOT use this code :
    //
    //     m_task = MakeTask( [=] { return *m_result; } );
    //
    //   In this case, the variable captured by lambda is 'this', not 'm_result'.
    //   And 'this' would be invalid after the local Promise is destroyed.
}


template< typename Result >
inline Promise< Result >::Promise( std::string taskName )
    : m_result( std::make_shared< Result >() )
{
    auto result = m_result;
    m_task = MakeTask( std::move( taskName ), [=] { return *result; });
}


template< typename Result >
inline void Promise< Result >::RunTask( Result result, TaskExecutor& executor )
{
    *m_result = result;
    executor.Submit( m_task );
}


template< typename Result >
inline void Promise< Result >::RunTask( Result result )
{
    StdAsyncProxy async;
    this->RunTask( result, async );

    // NOTES: You can't use the code:
    //
    //     this->RunTask( result, StdAsyncProxy() );
    //
    //   GCC doesn't not allow to pass a non-const reference of a temporary variable.
}


//
// Tasks return no values
//

inline Promise< void >::Promise()
    : m_task( [] {} )
{
}


inline Promise< void >::Promise( std::string taskName )
    : m_task( std::move( taskName ), [] {} )
{
}


inline void Promise< void >::RunTask( TaskExecutor& executor )
{
    executor.Submit( m_task );
}


inline void Promise< void >::RunTask()
{
    StdAsyncProxy async;
    this->RunTask( async );

    // NOTES: You can't use the code:
    //
    //     this->RunTask( StdAsyncProxy() );
    //
    //   GCC doesn't not allow to pass a non-const reference of a temporary variable.
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_PROMISE_H
