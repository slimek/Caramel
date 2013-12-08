// Caramel C++ Library - Thread Facility - Thread Implementation

#include "CaramelPch.h"

#include "Thread/ThreadIdImpl.h"
#include "Thread/ThreadImpl.h"
#include <Caramel/Error/CatchException.h>
#include <Caramel/Thread/ThisThread.h>
#include <sstream>

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )
#include <Windows.h>
#else
#include <pthread.h>
#endif


namespace Caramel
{

//
// Contents
//
//   Thread
//   ThreadId
//   ThisThread
//

///////////////////////////////////////////////////////////////////////////////
//
// Thread
//

Thread::Thread()
{
}


Thread::Thread( const std::string& name, WorkFunction work )
{
    this->Start( name, work );
}


Thread::~Thread()
{
}


void Thread::Start( const std::string& name, WorkFunction work )
{
    m_impl.reset( new ThreadImpl( name, work ));
}


void Thread::Join()
{
    CARAMEL_ASSERT( m_impl );
    m_impl->Join();
}


//
// Implemenation
//

ThreadImpl::ThreadImpl( const std::string& name, WorkFunction work )
    : m_name( name )
    , m_workFunction( work )
{
    m_thread.reset( new std::thread( [=] { this->RunWork(); } ));
    m_threadId = std::make_shared< ThreadIdImpl >( m_thread->get_id() );
}


void ThreadImpl::RunWork()
{
    auto xc = CatchException( m_workFunction );
    if ( xc )
    {
        CARAMEL_TRACE_WARN( "Exception caugut, thread name: %s", m_name );
    }
}


void ThreadImpl::Join()
{
    m_thread->join();
}


///////////////////////////////////////////////////////////////////////////////
//
// Thread ID
//

ThreadId::ThreadId()
{
}


ThreadId::ThreadId( ThreadIdPtr impl )
    : m_impl( impl )
{
}


//
// Properties
//

std::string ThreadId::ToString() const
{
    if ( ! m_impl ) { return "(null)"; }

    std::stringstream ss;
    ss << *m_impl;
    return ss.str();
}


Uint32 ThreadId::GetNativeId() const
{
    if ( ! m_impl ) { return 0; }

    if ( ! m_impl->m_nativeId )
    {
        CARAMEL_THROW( "Native id not supported in this system" );
    }

    return *( m_impl->m_nativeId );
}


//
// Implementation
//

ThreadIdImpl::ThreadIdImpl( const std::thread::id& threadId )
    : std::thread::id( threadId )
{
    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    {
        m_nativeId = ::GetCurrentThreadId();
    }
    #elif defined( CARAMEL_SYSTEM_IS_IOS ) || defined( CARAMEL_SYSTEM_IS_OSX )
    {
        m_nativeId = ::pthread_mach_thread_np( ::pthread_self() );
    }
    #elif defined( CARAMEL_SYSTEM_IS_ANDROID )
    {
        m_nativeId = ::pthread_self();
    }
    #endif
}


///////////////////////////////////////////////////////////////////////////////
//
// This Thread
//

ThreadId ThisThread::GetThreadId()
{
    return ThreadId( std::make_shared< ThreadIdImpl >( std::this_thread::get_id() ));
}


void ThisThread::SleepFor( const Ticks& duration )
{
    const std::chrono::milliseconds ms( duration.count() );
    std::this_thread::sleep_for( ms );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
