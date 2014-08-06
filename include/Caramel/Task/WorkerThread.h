// Caramel C++ Library - Task Facility - Worker Thread Header

#ifndef __CARAMEL_TASK_WORKER_THREAD_H
#define __CARAMEL_TASK_WORKER_THREAD_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Task/TaskExecutor.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Worker Thread
//

class WorkerThreadImpl;

class WorkerThread : public TaskExecutor
{
public:

    explicit WorkerThread( const std::string& name );
    ~WorkerThread();

    void Submit( TaskCore& task ) override;
    
    using TaskExecutor::Submit;

    // Blocks the calling thread, until the internal thread joined.
    void Stop();


private:

    void AddReadyTask( TaskCore& task ) override;

    std::shared_ptr< WorkerThreadImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_WORKER_THREAD_H
