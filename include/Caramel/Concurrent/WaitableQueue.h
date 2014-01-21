// Caramel C++ Library - Concurrent Amenity - Waitable Queue Header

#ifndef __CARAMEL_CONCURRENT_WAITABLE_QUEUE_H
#define __CARAMEL_CONCURRENT_WAITABLE_QUEUE_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Thread/MutexLocks.h>
#include <boost/noncopyable.hpp>
#include <condition_variable>
#include <deque>
#include <mutex>


namespace Caramel
{

namespace Concurrent
{

///////////////////////////////////////////////////////////////////////////////
//
// Waitable Concurrent Queue
//

template< typename T >
class WaitableQueue : public boost::noncopyable
{
public:

    /// Properties ///

    Bool IsEmpty() const { return m_queue.empty(); }


    /// Operations ///

    void Push( const T& x );
    void Push( T&& x );

    Bool TryPop( T& x );


    /// Waiting Available ///

    void WaitFor( const Ticks& ticks );
    void Awake();


private:

    typedef std::deque< T > QueueType;
    QueueType m_queue;

    std::mutex m_queueMutex;
    std::condition_varaible m_available;

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Operations
//

template< typename T >
inline void WaitableQueue< T >::Push( const T& value )
{
    {
        auto ulock = UniqueLock( m_queueMutex );
        m_queue.push_back( value );
    }

    m_available.notify_one();
}


template< typename T >
inline void WaitableQueue< T >::Push( T&& value )
{
    {
        auto ulock = UniqueLock( m_queueMutex );
        m_queue.push_back( std::move( value ));
    }

    m_available.notify_one();
}


template< typename T >
inline Bool WaitableQueue< T >::TryPop( T& value )
{
    if ( m_queue.empty() ) { return false; }

    auto ulock = UniqueLock( m_queueMutex );
    value = m_queue.front();
    m_queue.pop_front();
    return true;
}


//
// Waiting Available
//

template< typename T >
inline void WaitableQueue< T >::WaitFor( const Ticks& ticks )
{
    auto ulock = UniqueLock( m_queueMutex );
    m_available.wait_for( ulock, ticks );
}


template< typename T >
inline void WaitableQueue< T >::Awake()
{
    m_available.notify_all();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_WAITABLE_QUEUE_H
