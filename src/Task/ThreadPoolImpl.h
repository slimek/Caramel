// Caramel C++ Library - Task Facility - Thread Pool Private Header

#ifndef __CARAMEL_TASK_THREAD_POOL_IMPL_H
#define __CARAMEL_TASK_THREAD_POOL_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Task/PooledThread.h"
#include <Caramel/Task/ThreadPool.h>


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

private:

    std::string m_name;
    ThreadPool* m_host;
    
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_THREAD_POOL_IMPL_H
