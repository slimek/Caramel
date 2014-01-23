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
    m_impl->m_thread->join();
}


void Thread::Detach()
{
    CARAMEL_ASSERT( m_impl );
    m_impl->m_thread->detach();
}


//
// Properties
//

ThreadId Thread::GetId() const
{
    return ThreadId( m_impl->m_threadId );
}


//
// Implemenation
//

ThreadImpl::ThreadImpl( const std::string& name, WorkFunction work )
    : m_name( name )
    , m_workFunction( work )
{
    m_thread.reset( new std::thread( [=] { this->RunWork(); } ));
    m_started.Wait();
}


void ThreadImpl::RunWork()
{
    m_threadId = std::make_shared< ThreadIdImpl >( std::this_thread::get_id() );
    m_started = true;

    auto xc = CatchException( m_workFunction );
    if ( xc )
    {
        CARAMEL_TRACE_WARN( "Exception caugut, thread name: %s", m_name );
    }
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
// Operators
//

Bool ThreadId::operator==( const ThreadId& rhs ) const
{
    if ( ! m_impl && ! rhs.m_impl ) { return true; }  // Both are "not a thread"

    if ( ! m_impl || ! rhs.m_impl ) { return false; }

    return *m_impl == *rhs.m_impl;
}


Bool ThreadId::operator<( const ThreadId& rhs ) const
{
    if ( ! m_impl && ! rhs.m_impl ) { return false; }

    if ( ! m_impl && rhs.m_impl ) { return true; }
    if ( m_impl && ! rhs.m_impl ) { return false; }

    return *m_impl < *rhs.m_impl;
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

ThreadId ThisThread::GetId()
{
    return ThreadId( std::make_shared< ThreadIdImpl >( std::this_thread::get_id() ));
}


void ThisThread::SleepFor( const Ticks& duration )
{
    std::this_thread::sleep_for( duration.ToStdDuration() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
