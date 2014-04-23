// Caramel C++ Library - Thread Facility - Loop Thread Group Private Header

#ifndef __CARAMEL_THREAD_LOOP_THREAD_GROUP_IMPL_H
#define __CARAMEL_THREAD_LOOP_THREAD_GROUP_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Thread/ThreadImpl.h"
#include <Caramel/Thread/LoopThreadGroup.h>
#include <Caramel/Thread/WaitableBool.h>
#include <unordered_set>
#include <mutex>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Loop Thread
//

class LoopThread
{
public:

    LoopThread( const std::string& name, WorkFunction&& work, const Ticks& interval );

    void Stop();
    void Join();


private:

    void RepeatWork();

    WorkFunction m_workFunction;
    Ticks m_interval;

    std::unique_ptr< ThreadImpl > m_thread;

    WaitableBool m_stopped;
};

typedef std::shared_ptr< LoopThread > LoopThreadPtr;


///////////////////////////////////////////////////////////////////////////////
//
// Loop Thread Group
//

class LoopThreadGroupImpl
{
public:

    void Add( LoopThreadPtr&& thread );

    void StopAll();
    

private:

    std::mutex m_mutex;

    typedef std::unordered_set< LoopThreadPtr > ThreadSet;
    ThreadSet m_threads;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_LOOP_THREAD_GROUP_IMPL_H
