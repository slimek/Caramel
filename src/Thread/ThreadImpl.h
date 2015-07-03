// Caramel C++ Library - Thread Facility - Thread Private Header

#ifndef __CARAMEL_THREAD_THREAD_IMPL_H
#define __CARAMEL_THREAD_THREAD_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Thread/ThreadIdImpl.h"
#include <Caramel/Thread/Thread.h>
#include <Caramel/Thread/WaitableBool.h>
#include <thread>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Thread
//

class ThreadImpl
{
    friend class Thread;
    friend class LoopThread;

public:

    ThreadImpl( std::string&& name, WorkFunction&& work );


    // Set the handler when the thread exits.
    void SetAtExit( std::function< void() > atExit );


private:

    void RunWork();

    std::string  m_name;
    WorkFunction m_workFunction;

    std::unique_ptr< std::thread > m_thread;

    ThreadIdPtr  m_threadId;
    WaitableBool m_started;

    std::function< void() > m_atExit { nullptr };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_THREAD_IMPL_H
