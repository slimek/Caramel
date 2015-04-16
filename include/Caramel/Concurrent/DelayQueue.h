// Caramel C++ Library - Concurrent Amenity - Delay Queue Header

#ifndef __CARAMEL_CONCURRENT_DELAY_QUEUE_H
#define __CARAMEL_CONCURRENT_DELAY_QUEUE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Chrono/SecondClock.h>
#include <Caramel/Thread/MutexLocks.h>
#include <boost/noncopyable.hpp>
#include <deque>


namespace Caramel
{

namespace Concurrent
{

///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Delay Queue
// - You may retrieve the element only after it has been expired since pushed.
//

template< typename T >
class DelayQueue : public boost::noncopyable
{
public:
    
    explicit DelayQueue( Seconds delay );


    /// Properties ///

    Bool IsEmpty() const { return m_queue.empty(); }


    /// Operations ///

    void Push( const T& x );
    void Push( T&& x );

    Bool TryPop( T& x );

    
private:

    /// Data Members ///

    Seconds m_delay;

    struct Entry
    {
        T item;
        SecondPoint expires;
    };

    typedef std::deque< Entry > QueueType;
    QueueType m_queue;

    mutable std::mutex m_queueMutex;
        
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T >
DelayQueue< T >::DelayQueue( Seconds delay )
    : m_delay( delay )
{}


//
// Operations
//

template< typename T >
inline void DelayQueue< T >::Push( const T& x )
{
    LockGuard lock( m_queueMutex );

    m_queue.push_back( Entry{ x, SecondClock::Now() + m_delay });
}


template< typename T >
inline void DelayQueue< T >::Push( T&& x )
{
    LockGuard lock( m_queueMutex );

    m_queue.push_back( Entry{ std::move( x ), SecondClock::Now() + m_delay });
}


template< typename T >
inline Bool DelayQueue< T >::TryPop( T& x )
{
    if ( m_queue.empty() ) { return false; }

    LockGuard lock( m_queueMutex );

    if ( m_queue.empty() ) { return false; }

    const Entry& e = m_queue.front();
    if ( e.expires < SecondClock::Now() )
    {
        x = e.item;
        m_queue.pop_front();
        return true;
    }

    return false;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_DELAY_QUEUE_H
