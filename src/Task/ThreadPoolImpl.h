// Caramel C++ Library - Task Facility - Thread Pool Private Header

#ifndef __CARAMEL_TASK_THREAD_POOL_IMPL_H
#define __CARAMEL_TASK_THREAD_POOL_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Task/PooledThread.h"
#include <Caramel/Concurrent/Queue.h>
#include <Caramel/Concurrent/Stack.h>
#include <Caramel/Task/ThreadPool.h>
#include <boost/ptr_container/ptr_vector.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Thread Pool
//

class ThreadPoolImpl
{
public:

    ThreadPoolImpl( const std::string& name, Uint numThreads, ThreadPool* host );
    ~ThreadPoolImpl();


    /// Properties ///

    std::string GetName() const { return m_name; }


    /// Operations ///

    void Shutdown();

    void AddReadyTask( TaskCore& task );
    void AddReadyThread( PooledThread* thread );


private:

    void TryDispatchOneTask();


    /// Data Members ///

    std::string m_name;
    ThreadPool* m_host;
    
    Bool m_shutdown;

    boost::ptr_vector< PooledThread > m_threads;

    typedef Concurrent::Stack< PooledThread* > ThreadStack;
    ThreadStack m_readyThreads;

    typedef Concurrent::Queue< TaskCore > TaskQueue;
    TaskQueue m_readyTasks;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_THREAD_POOL_IMPL_H
