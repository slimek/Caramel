// Caramel C++ Library - Concurrent Amenity - Bounded Queue Header

#ifndef __CARAMEL_CONCURRENT_BOUNDED_QUEUE_H
#define __CARAMEL_CONCURRENT_BOUNDED_QUEUE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Error/Assert.h>
#include <Caramel/Thread/MutexLocks.h>
#include <boost/noncopyable.hpp>
#include <deque>


namespace Caramel
{

namespace Concurrent
{

///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Bounded Queue
// - A queue with fixed capacity.
//   If you push items when the queue is full, it may:
//
//   1. TryPush : Returns false.
//   2. ForcePush : Discards the front element to accept this new element.
//

template< typename T >
class BoundedQueue : public boost::noncopyable
{
public:

    // Capacity should not be 0.
    explicit BoundedQueue( Usize capacity );


    /// Properties ///

    Bool  IsEmpty() const { return m_queue.empty(); }
    Usize Size()    const { return m_queue.size(); }


    /// Operations ///

    // Returns false if the queue is full.
    Bool TryPush( const T& value );
    Bool TryPush( T&& value );

    // Returns false if the queue is full.
    // - i.e. This pushing is still successful, but the front element is discarded.
    Bool ForcePush( const T& value );
    Bool ForcePush( T&& value );

    Bool TryPop( T& value );


private:

    typedef std::deque< T > QueueType;
    QueueType m_queue;

    Usize m_capacity;

    std::mutex m_queueMutex;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T >
inline BoundedQueue< T >::BoundedQueue( Usize capacity )
    : m_capacity( capacity )
{
    CARAMEL_ASSERT( capacity > 0 );
}


//
// Operations
//

template< typename T >
inline Bool BoundedQueue< T >::TryPush( const T& value )
{
    LockGuard lock( m_queueMutex );

    if ( m_capacity == m_queue.size() ) { return false; }

    m_queue.push_back( value );
    return true;
}


template< typename T >
inline Bool BoundedQueue< T >::TryPush( T&& value )
{
    LockGuard lock( m_queueMutex );

    if ( m_capacity == m_queue.size() ) { return false; }

    m_queue.push_back( std::move( value ));
    return true;
}


template< typename T >
inline Bool BoundedQueue< T >::ForcePush( const T& value )
{
    LockGuard lock( m_queueMutex );

    Bool noDiscard = true;

    if ( m_capacity == m_queue.size() )
    {
        m_queue.pop_front();
        noDiscard = false;
    }

    m_queue.push_back( value );
    return noDiscard;
}


template< typename T >
inline Bool BoundedQueue< T >::ForcePush( T&& value )
{
    LockGuard lock( m_queueMutex );

    Bool noDiscard = true;

    if ( m_capacity == m_queue.size() )
    {
        m_queue.pop_front();
        noDiscard = false;
    }

    m_queue.push_back( std::move( value ));
    return noDiscard;
}


template< typename T >
inline Bool BoundedQueue< T >::TryPop( T& value )
{
    if ( m_queue.empty() ) { return false; }

    LockGuard lock( m_queueMutex );

    if ( m_queue.empty() ) { return false; }

    value = m_queue.front();
    m_queue.pop_front();

    return true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_BOUNDED_QUEUE_H
