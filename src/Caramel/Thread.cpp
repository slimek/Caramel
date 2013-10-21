// Caramel C++ Library - Thread Facility - Thread Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Error/CatchException.h>
#include <Caramel/Thread/ThisThread.h>
#include <Caramel/Thread/ThreadImpl.h>


namespace Caramel
{

//
// Contents
//
//   Thread
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
// This Thread
//

Uint ThisThread::GetThreadId()
{
    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    {
        return ::GetCurrentThreadId();
    }
    #elif defined( CARAMEL_SYSTEM_IS_IOS )
    {
        return ::pthread_mach_thread_np( ::pthread_self() );
    }
    #elif defined( CARAMEL_SYSTEM_IS_ANDROID )
    {
        return ::pthread_self();
    }
    #else
    {
        CARAMEL_NOT_IMPLEMENTED();
    }
    #endif    
}


void ThisThread::SleepFor( const TickDuration& duration )
{
    const std::chrono::milliseconds ms( duration.count() );
    std::this_thread::sleep_for( ms );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
