// Caramel C++ Library - Thread Facility - Thread Private Header

#ifndef __CARAMEL_THREAD_THREAD_IMPL_H
#define __CARAMEL_THREAD_THREAD_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Thread/Thread.h>
#include <thread>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Thread
//

class ThreadImpl
{
public:

    ThreadImpl( const std::string& name, WorkFunction work );

    void Join();


private:

    void RunWork();

    std::string  m_name;
    WorkFunction m_workFunction;

    std::unique_ptr< std::thread > m_thread;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_THREAD_IMPL_H
