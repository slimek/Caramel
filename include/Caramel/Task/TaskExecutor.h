// Caramel C++ Library - Task Facility - Task Executor Header

#ifndef __CARAMEL_TASK_TASK_EXECUTOR_H
#define __CARAMEL_TASK_TASK_EXECUTOR_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Task/Task.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Executor
// - Abstract
//

class TaskExecutor
{
    friend class TaskImpl;

public:
    
    virtual ~TaskExecutor() {}

    virtual void Submit( TaskCore& task ) = 0;


    // Compiler Workaround :
    // - Some compiler doesn't allow to convert a rvalue to non-const lvalue implicity.
    //   This function may change a rvalue to a lvalue.
    void Submit( TaskCore&& task )
    {
        this->Submit( task );
    }


    // Directly submit a function into a task.
    template< typename Function >
    auto Submit( const std::string& taskName, Function taskFunction )
        -> Task< decltype( taskFunction() ) >;


private:

    // This function is only called by Task internally.
    virtual void AddReadyTask( TaskCore& task ) = 0;

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Function >
inline auto TaskExecutor::Submit(
    const std::string& taskName, Function taskFunction )
        -> Task< decltype( taskFunction() ) >
{
    auto task = MakeTask( taskName, std::move( taskFunction ));
    this->Submit( task );
    return task;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_EXECUTOR_H
