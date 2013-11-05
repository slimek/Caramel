// Caramel C++ Library - Concurrent Amenity - Queue Header

#ifndef __CARAMEL_CONCURRENT_QUEUE_H
#define __CARAMEL_CONCURRENT_QUEUE_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Thread/MutexLocks.h>
#include <boost/noncopyable.hpp>
#include <deque>


namespace Caramel
{

namespace Concurrent
{

///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Queue
//

template< typename T >
class Queue : public boost::noncopyable
{
public:

    /// Operations ///

    void Push( const T& x );

    Bool TryPop( T& x );


    /// Not Thread-safe Properties ///

    Bool IsEmpty() const { return m_queue.empty(); }


private:

    typedef std::deque< T > QueueType;
    QueueType m_queue;

    std::mutex m_queueMutex;
};


//
// Implementation
//

template< typename T >
inline void Queue< T >::Push( const T& x )
{
    auto ulock = UniqueLock( m_queueMutex );

    m_queue.push_back( x );
}


template< typename T >
inline Bool Queue< T >::TryPop( T& x )
{
    if ( m_queue.empty() ) { return false; }

    auto ulock = UniqueLock( m_queueMutex );

    if ( m_queue.empty() ) { return false; }

    x = m_queue.front();
    m_queue.pop_front();

    return true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_QUEUE_H
