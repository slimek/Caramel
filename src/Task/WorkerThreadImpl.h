// Caramel C++ Library - Task Facility - Worker Thread Private Header

#ifndef __CARAMEL_TASK_WORKER_THREAD_IMPL_H
#define __CARAMEL_TASK_WORKER_THREAD_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Task/TaskImpl.h"
#include <Caramel/Concurrent/PriorityQueue.h>
#include <Caramel/Concurrent/BlockingQueue.h>
#include <Caramel/Task/WorkerThread.h>
#include <Caramel/Thread/Thread.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Worker Thread
//

class WorkerThreadImpl
{
    friend class WorkerThread;

public:

    WorkerThreadImpl( const std::string& name, WorkerThread* host );

private:

    /// Thread Execution ///

    void Execute();


    /// Data Members ///

    std::string m_name;
    WorkerThread* m_host;

    std::unique_ptr< Thread > m_thread;
    Bool m_stopped;

    Concurrent::ReversePriorityQueue< TickPoint, TaskCore > m_delayTasks;
    Concurrent::BlockingQueue< TaskCore > m_readyTasks;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_WORKER_THREAD_IMPL_H
