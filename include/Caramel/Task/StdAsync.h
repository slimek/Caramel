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
// - Execute the tasks and all its first continuations with std::async().
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
// - A task executor based on std::async()
//   This Executor doesn't support Delay of tasks.
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
    auto task = MakeTask( taskFunction );
    StdAsync::Submit( task );
    return task;
}


template< typename Function >
inline auto StdAsync::Submit( std::string taskName, Function taskFunction ) -> Task< decltype( taskFunction() ) >
{
    auto task = MakeTask( taskName, taskFunction );
    StdAsync::Submit( task );
    return task;
}


///////////////////////////////////////////////////////////////////////////////


} // namespace Caramel

#endif // __CARAMEL_TASK_STD_ASYNC_H
