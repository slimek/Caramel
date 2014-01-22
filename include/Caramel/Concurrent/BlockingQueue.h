// Caramel C++ Library - Concurrent Amenity - Blocking Queue Header

#ifndef __CARAMEL_CONCURRENT_BLOCKING_QUEUE_H
#define __CARAMEL_CONCURRENT_BLOCKING_QUEUE_H
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
// Concurrent Blocking Queue
//

template< typename T >
class BlockingQueue : public boost::noncopyable
{
public:

    /// Properties ///

    Bool IsEmpty() const { return m_queue.empty(); }


    /// Operations ///

    void Push( const T& value );
    void Push( T&& value );

    // true  - Pop an element
    // false - Timeout, or pulsed by PulseAll()
    Bool PopOrWait( T& value, const Ticks& ticks );

    // All waiting threads will return from PopOrWait() with false.
    void PulseAll();


private:

    typedef std::deque< T > QueueType;
    QueueType m_queue;

    std::mutex m_queueMutex;
    std::condition_variable m_available;

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Operations
//

template< typename T >
inline void BlockingQueue< T >::Push( const T& value )
{
    {
        auto ulock = UniqueLock( m_queueMutex );
        m_queue.push_back( value );
    }

    m_available.notify_one();
}


template< typename T >
inline void BlockingQueue< T >::Push( T&& value )
{
    {
        auto ulock = UniqueLock( m_queueMutex );
        m_queue.push_back( std::move( value ));
    }

    m_available.notify_one();
}


template< typename T >
inline Bool BlockingQueue< T >::PopOrWait( T& value, const Ticks& ticks )
{
    auto ulock = UniqueLock( m_queueMutex );

    if ( m_queue.empty() )
    {
        m_available.wait_for( ulock, ticks );

        if ( m_queue.empty() ) { return false; }

        // When timeout or pulsed,
        // If by chance the queue has elements, we may pop it.
    }

    value = m_queue.front();
    m_queue.pop_front();

    return true;
}


//
// Waiting Available
//

template< typename T >
inline void BlockingQueue< T >::PulseAll()
{
    m_available.notify_all();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_BLOCKING_QUEUE_H
