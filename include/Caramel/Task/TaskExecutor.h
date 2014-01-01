// Caramel C++ Library - Task Facility - Task Executor Header

#ifndef __CARAMEL_TASK_TASK_EXECUTOR_H
#define __CARAMEL_TASK_TASK_EXECUTOR_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Task/Detail/TaskFwd.h>
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

    virtual void Submit( Task& task ) = 0;


private:

    // This function is only called by Task internally.
    virtual void AddTaskToReady( Task& task ) = 0;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_EXECUTOR_H
