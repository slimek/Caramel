// Caramel C++ Library - Task Facility - Task Executor Header

#ifndef __CARAMEL_TASK_TASK_EXECUTOR_H
#define __CARAMEL_TASK_TASK_EXECUTOR_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

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
public:
    virtual ~TaskExecutor() {}

    virtual void Submit( const Task& task ) = 0;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_EXECUTOR_H
