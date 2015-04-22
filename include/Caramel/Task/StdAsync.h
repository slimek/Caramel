// Caramel C++ Library - Task Facility - Task Poller Header

#ifndef __CARAMEL_TASK_STD_ASYNC_H
#define __CARAMEL_TASK_STD_ASYNC_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Task/TaskExecutor.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Std Async
// - Execute the tasks and all their continuations with std::async().
//

class StdAsync
{
public:

    static void Submit( TaskCore& task );

    // Compiler workaround :
    // - Some compilers do not allow to convert a rvalue to non-const lvalue implicitly.
    //   This function may change a rvalue to a lvalue.
    static void Submit( TaskCore&& task )
    {
        Submit( task );
    }

    
    // Directly submit a function into a task.

    template< typename Function >
    static auto Submit( Function taskFunction ) -> Task< decltype( taskFunction() ) >;

    template< typename Function >
    static auto Submit( std::string taskName, Function taskFunction )
        -> Task< decltype( taskFunction() ) >;


private:
    
    StdAsync() = delete;
};


///////////////////////////////////////////////////////////////////////////////
//
// Std Async Proxy
// - It would submit the task to StdAsync.
//   Use this type when you need to pass a TaskExecutor parameter, and want to
//   execute the tasks in StdAsync.
// 

class StdAsyncProxy : public TaskExecutor
{
public:

    void Submit( TaskCore& task ) override;

    using TaskExecutor::Submit;
    
private:

    void AddReadyTask( TaskCore& task ) override;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Function >
inline auto StdAsync::Submit( Function taskFunction ) -> Task< decltype( taskFunction() ) >
{
    auto task = MakeTask( std::move( taskFunction ));
    StdAsync::Submit( task );
    return task;
}


template< typename Function >
inline auto StdAsync::Submit(
    std::string taskName, Function taskFunction ) -> Task< decltype( taskFunction() ) >
{
    auto task = MakeTask( std::move( taskName ), std::move( taskFunction ));
    StdAsync::Submit( task );
    return task;
}


///////////////////////////////////////////////////////////////////////////////


} // namespace Caramel

#endif // __CARAMEL_TASK_STD_ASYNC_H
