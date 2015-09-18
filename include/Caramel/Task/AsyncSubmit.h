// Caramel C++ Library - Task Facility - Async Submit Header

#ifndef __CARAMEL_TASK_ASYNC_SUBMIT_H
#define __CARAMEL_TASK_ASYNC_SUBMIT_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Task/TaskExecutor.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Async Submit
//

void AsyncSubmit( TaskCore& task );

// Compiler workaround :
// - Some compilers do not allow to convert a rvalue to non-const lvalue implicitly.
//   This function may change a rvalue to a lvalue.
void AsyncSubmit( TaskCore&& task );


// Directly submit a function into a task

template< typename Function >
static auto AsyncSubmit( Function taskFunction ) -> Task< decltype( taskFunction() ) >;

template< typename Function >
static auto AsyncSubmit( std::string taskName, Function taskFunction )
    -> Task< decltype( taskFunction() ) >;


///////////////////////////////////////////////////////////////////////////////
//
// Async Submit Proxy
// - It submits tasks to AsyncSubmit.
//   Use this class when you need a TaskExecutor parameter, and want to execute
//   the tasks by AsyncSubmit.
//

class AsyncSubmitProxy : public TaskExecutor
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
inline auto AsyncSubmit( Function taskFunction ) -> Task< decltype( taskFunction() ) >
{
    auto task = MakeTask( std::move( taskFunction ));
    AsyncSubmit( task );
    return task;
}


template< typename Function >
inline auto AsyncSubmit( std::string taskName, Function taskFunction )
    -> Task< decltype( taskFunction() ) >
{
    auto task = MakeTask( std::move( taskName ), std::move( taskFunction ));
    AsyncSubmit( task );
    return task;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_ASYNC_SUBMIT_H
