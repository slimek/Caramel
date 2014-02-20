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
//

class StdAsyncImpl;

class StdAsync : public TaskExecutor
{
public:

    StdAsync();

    void Submit( TaskCore& task ) override;
    void Submit( TaskCore&& task ) override;


private:

    void AddReadyTask( TaskCore& task ) override;

    std::shared_ptr< StdAsyncImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////


} // namespace Caramel

#endif // __CARAMEL_TASK_STD_ASYNC_H
