// Caramel C++ Library - Task Facility - Pooled Thread Header

#ifndef __CARAMEL_TASK_POOLED_THREAD_H
#define __CARAMEL_TASK_POOLED_THREAD_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Task/TaskImpl.h"
#include <Caramel/Thread/Thread.h>
#include <condition_variable>
#include <mutex>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Pooled Thread
//

class ThreadPoolImpl;

class PooledThread
{
public:

    PooledThread( ThreadPoolImpl* threadPool, Uint index );


    /// Operations ///

    void Wake( TaskCore& task );
    void StopAndJoin();


private:

    void Execute();


    /// Data Members ///

    ThreadPoolImpl* m_threadPool;
    std::string     m_name;

    std::shared_ptr< Thread > m_thread;
    Bool m_stopped;

    TaskCore m_runningTask;

    mutable std::mutex m_mutex;
    std::condition_variable m_waken;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_POOLED_THREAD_H
