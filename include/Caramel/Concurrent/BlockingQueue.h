// Caramel C++ Library - Concurrent Amenity - Blocking Queue Header

#ifndef __CARAMEL_CONCURRENT_BLOCKING_QUEUE_H
#define __CARAMEL_CONCURRENT_BLOCKING_QUEUE_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Error/Exception.h>
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

    BlockingQueue();


    /// Properties ///

    Bool IsEmpty() const { return m_queue.empty(); }


    /// Operations ///

    void Push( const T& value );
    void Push( T&& value );

    // true  - Pop an element
    // false - Timeout, or pulsed by PulseAll() and Complete()
    Bool PopOrWaitFor( T& value, const Ticks& ticks );

    // Force all waiting threads return from PopOrWaitFor().
    void PulseAll();

    // Make this queue accepting NO MORE pushes. This has 3 effects:
    //   1. All current waiting threads would return from PopOrWaitFor().
    //   2. Later Push() would throw exceptions.
    //   3. If this queue becomes empty, later PopOrWaitFor() would return false immediately.
    void Complete();


private:

    typedef std::deque< T > QueueType;
    QueueType m_queue;

    Bool m_completed;

    std::mutex m_queueMutex;
    std::condition_variable m_available;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T >
inline BlockingQueue< T >::BlockingQueue()
    : m_completed( false )
{
}


//
// Operations
//

template< typename T >
inline void BlockingQueue< T >::Push( const T& value )
{
    {
        auto ulock = UniqueLock( m_queueMutex );

        if ( m_completed )
        {
            CARAMEL_THROW( "BlockingQueue has been completed" );
        }

        m_queue.push_back( value );
    }

    m_available.notify_one();
}


template< typename T >
inline void BlockingQueue< T >::Push( T&& value )
{
    {
        auto ulock = UniqueLock( m_queueMutex );

        if ( m_completed )
        {
            CARAMEL_THROW( "BlockingQueue has been completed" );
        }

        m_queue.push_back( std::move( value ));
    }

    m_available.notify_one();
}


template< typename T >
inline Bool BlockingQueue< T >::PopOrWaitFor( T& value, const Ticks& ticks )
{
    auto ulock = UniqueLock( m_queueMutex );

    if ( m_queue.empty() )
    {
        if ( m_completed ) { return false; }

        m_available.wait_for( ulock, ticks.ToStdDuration() );

        if ( m_queue.empty() ) { return false; }

        // When timeout or pulsed,
        // If by chance the queue has elements, we may pop it.
    }

    value = m_queue.front();
    m_queue.pop_front();

    return true;
}


template< typename T >
inline void BlockingQueue< T >::PulseAll()
{
    m_available.notify_all();
}


template< typename T >
inline void BlockingQueue< T >::Complete()
{
    {
        auto ulock = UniqueLock( m_queueMutex );
        m_completed = true;
    }

    m_available.notify_all();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_BLOCKING_QUEUE_H
