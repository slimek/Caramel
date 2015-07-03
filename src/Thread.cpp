// Caramel C++ Library - Thread Facility - Thread Implementation

#include "CaramelPch.h"

#include "Thread/LoopThreadGroupImpl.h"
#include "Thread/ThreadIdImpl.h"
#include "Thread/ThreadImpl.h"
#include <Caramel/Error/CatchException.h>
#include <Caramel/Memory/UniquePtrUtils.h>
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
//   LoopThread
//   LoopThreadGroup
//

//
// Thread Local Storages
// - NOTES: In Xcode 5.1 , Clang supports the keyword 'thread_local',
//          But its C++ Runtime Library (libc++) not...
//

#if ! defined( CARAMEL_SYSTEM_OF_APPLE )

#define HAS_THREAD_LOCAL

// This would be set before the thread's working function starts.
CARAMEL_THREAD_LOCAL ThreadImpl* tls_thisThread = nullptr;

#endif



///////////////////////////////////////////////////////////////////////////////
//
// Thread
//

Thread::Thread()
{
}


Thread::Thread( std::string name, WorkFunction work )
{
    this->Start( std::move( name ), std::move( work ));
}


Thread::~Thread()
{
}


void Thread::Start( std::string name, WorkFunction work )
{
    m_impl.reset( new ThreadImpl( std::move( name ), std::move( work )));
}


void Thread::Join()
{
    CARAMEL_ASSERT( m_impl );
    m_impl->m_thread->join();
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

ThreadImpl::ThreadImpl( std::string&& name, WorkFunction&& work )
    : m_name( std::move( name ))
    , m_workFunction( std::move( work ))
{
    m_thread.reset( new std::thread( [=] { this->RunWork(); } ));
    m_started.Wait();
}


void ThreadImpl::RunWork()
{
    // Thread keeps a reference to itself.
    //auto thiz = this->shared_from_this();

    m_threadId = std::make_shared< ThreadIdImpl >( std::this_thread::get_id() );
    
    #if defined( HAS_THREAD_LOCAL )
    {
        tls_thisThread = this;
    }
    #endif

    m_started = true;

    auto workXc = CatchException( m_workFunction );
    if ( workXc )
    {
        CARAMEL_ALERT( "Thread[{0}] caugut exception:\n{1}", m_name, workXc.TracingMessage() );
    }

    if ( m_atExit )
    {
        auto exitXc = CatchException( m_atExit );
        if ( exitXc )
        {
            CARAMEL_ALERT( "Thread[{0}].atExit() throws:\n{1}", m_name, exitXc.TracingMessage() );
        }
    }
}


void ThreadImpl::SetAtExit( std::function< void() > atExit )
{
    CARAMEL_ASSERT( *m_threadId == std::this_thread::get_id() );
    CARAMEL_ASSERT( ! m_atExit );

    m_atExit = atExit;
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


void ThisThread::Yield()
{
    std::this_thread::yield();
}


void ThisThread::AtThreadExit( std::function< void() > atExit )
{
    #if defined( HAS_THREAD_LOCAL )
    {
        if ( tls_thisThread )
        {
            tls_thisThread->SetAtExit( atExit );
        }
        else
        {
            CARAMEL_ALERT( "This thread is not a Caramel thread" );
        }
    }
    #else
    {
        CARAMEL_NOT_IMPLEMENTED();
    }
    #endif
}


///////////////////////////////////////////////////////////////////////////////
//
// Loop Thread
//

LoopThread::LoopThread( std::string&& name, Ticks&& interval, WorkFunction&& work )
    : m_workFunction( std::move( work ))
    , m_interval( std::move( interval ))
{
    m_thread.reset( new ThreadImpl( std::move( name ), [this] { this->RepeatWork(); } ));
}


void LoopThread::RepeatWork()
{
    while ( ! m_stopped )
    {
        /// Sleep for Interval ///

        if ( Ticks::Zero() == m_interval )
        {
            ThisThread::Yield();
        }
        else
        {
            m_stopped.WaitFor( m_interval );
        }

        if ( m_stopped ) { break; }


        /// Execute the Work ///

        auto xc = CatchException( m_workFunction );

        if ( xc )
        {
            CARAMEL_ALERT( "Thread[{0}] throws exception: {1}", m_thread->m_name, xc.TracingMessage() );
        }

    }
}


void LoopThread::Stop()
{
    m_stopped = true;
}


void LoopThread::Join()
{
    m_thread->m_thread->join();
}


///////////////////////////////////////////////////////////////////////////////
//
// Loop Thread Group
//

LoopThreadGroup::LoopThreadGroup()
    : m_impl( new LoopThreadGroupImpl )
{
}


LoopThreadGroup::~LoopThreadGroup()
{
}


void LoopThreadGroup::Start( std::string name, Ticks interval, WorkFunction work )
{
    m_impl->Add( std::make_shared< LoopThread >(
        std::move( name ), std::move( interval ), std::move( work )));
}


void LoopThreadGroup::StopAll()
{
    m_impl->StopAll();
}


//
// Implementation
//

void LoopThreadGroupImpl::Add( LoopThreadPtr&& thread )
{
    LockGuard lock( m_mutex );

    m_threads.insert( std::move( thread ));
}


void LoopThreadGroupImpl::StopAll()
{
    LockGuard lock( m_mutex );

    for ( auto thread : m_threads )
    {
        thread->Stop();
    }

    for ( auto thread : m_threads )
    {
        thread->Join();
    }

    m_threads.clear();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
