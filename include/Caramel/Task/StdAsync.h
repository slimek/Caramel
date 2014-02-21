// Caramel C++ Library - Task Facility - Task Poller Header

#ifndef __CARAMEL_TASK_STD_ASYNC_H
#define __CARAMEL_TASK_STD_ASYNC_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Task/Detail/TaskFwd.h>
#include <Caramel/Task/TaskExecutor.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Std Async
// - A task executor based on std::async()
//   This Executor doesn't support Delay of tasks.
//

class StdAsync : public TaskExecutor
{
public:

    void Submit( TaskCore& task ) override;


private:

    void AddReadyTask( TaskCore& task ) override;
};


///////////////////////////////////////////////////////////////////////////////


} // namespace Caramel

#endif // __CARAMEL_TASK_STD_ASYNC_H
