// Caramel C++ Library - Task Facility - Thread Pool Header

#ifndef __CARAMEL_TASK_THREAD_POOL_H
#define __CARAMEL_TASK_THREAD_POOL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Task/TaskExecutor.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Thread Pool
//

class ThreadPoolImpl;

class ThreadPool : public TaskExecutor
{
public:

    ThreadPool( const std::string& name, Uint numThreads );
    ~ThreadPool();

    void Submit( TaskCore& task ) override;

    using TaskExecutor::Submit;   
    
    // Discard all tasks not running,
    // then blocks the calling thread until all the pooled threads joined.
    void Shutdown();


    /// Properties ///

    Uint GetNumReadyTasks() const;


private:

    void AddReadyTask( TaskCore& task ) override;

    std::shared_ptr< ThreadPoolImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_THREAD_POOL_H
