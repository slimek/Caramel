// Caramel C++ Library - Task Facility - Pooled Thread Header

#ifndef __CARAMEL_TASK_POOLED_THREAD_H
#define __CARAMEL_TASK_POOLED_THREAD_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Task/TaskImpl.h"


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

    void Wake( const TaskCore& task );
    void Stop();

private:

    
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_POOLED_THREAD_H
