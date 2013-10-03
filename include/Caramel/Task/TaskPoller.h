// Caramel C++ Library - Task Facility - Task Poller Header

#ifndef __CARAMEL_TASK_TASK_POLLER_H
#define __CARAMEL_TASK_TASK_POLLER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Task/TaskExecutor.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Poller
//

class TaskPollerImpl;

class TaskPoller : public TaskExecutor
{
public:

    TaskPoller();

    void Submit( const Task& task ) override;

    void PollOne();


private:

    std::shared_ptr< TaskPollerImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_TASK_POLLER_H
