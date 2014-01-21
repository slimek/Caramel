// Caramel C++ Library - Task Facility - Worker Thread Header

#ifndef __CARAMEL_TASK_WORKER_THREAD_H
#define __CARAMEL_TASK_WORKER_THREAD_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Task/Detail/TaskFwd.h>
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

    void Submit( Task& task ) override;

    void Stop();


private:

    void AddReadyTask( Task& task ) override;

    std::shared_ptr< WorkerThreadImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TASK_WORKER_THREAD_H
