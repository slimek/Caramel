// Caramel C++ Library - Concurrent Amenity - Queue Header

#ifndef __CARAMEL_CONCURRENT_QUEUE_H
#define __CARAMEL_CONCURRENT_QUEUE_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Concurrent/ReplicatePolicies.h>
#include <Caramel/Concurrent/Detail/LockedSequence.h>
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

template< typename T, typename ReplicatePolicy = ReplicateNothing >
class Queue : public ReplicatePolicy::template Collection
              <
                  Queue< T, ReplicatePolicy >, T
              >
            , public boost::noncopyable
{
public:

    typedef T ValueType;

    typedef typename ReplicatePolicy::template Collection
    <
        Queue< T, ReplicatePolicy >, T
    >
    Replicator;


    /// Properties ///

    Bool IsEmpty() const { return m_queue.empty(); }
    Uint Size()    const { return static_cast< Uint >( m_queue.size() ); }


    /// Operations ///

    void Push( const T& x );
    void Push( T&& x );

    Bool TryPop( T& x );

    void Clear();


    /// Locked Iterator Accessor ///

    class ConstLockedQueue;
    friend class ConstLockedQueue;

    // For Replicator
    typedef ConstLockedQueue ConstLockedCollection;


private:

    /// Data Members ///

    typedef std::deque< T > QueueType;
    QueueType m_queue;

    mutable std::mutex m_queueMutex;
};


//
// Convenient Alias
//

template< typename T >
class QueueWithSnapshot : public Queue< T, ReplicateSnapshot >
{
};



///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T, typename ReplicateP >
inline void Queue< T, ReplicateP >::Push( const T& x )
{
    auto ulock = UniqueLock( m_queueMutex );

    m_queue.push_back( x );

    this->Replicator::ReplicaAdd( x );
}


template< typename T, typename ReplicateP >
inline void Queue< T, ReplicateP >::Push( T&& x )
{
    auto ulock = UniqueLock( m_queueMutex );

    m_queue.push_back( std::move( x ));

    this->Replicator::ReplicaAdd( m_queue.back() );
}


template< typename T, typename ReplicateP >
inline Bool Queue< T, ReplicateP >::TryPop( T& x )
{
    if ( m_queue.empty() ) { return false; }

    auto ulock = UniqueLock( m_queueMutex );

    if ( m_queue.empty() ) { return false; }

    x = m_queue.front();
    m_queue.pop_front();

    this->Replicator::ReplicaRemove( x );

    return true;
}


template< typename T, typename ReplicateP >
inline void Queue< T, ReplicateP >::Clear()
{
    auto ulock = UniqueLock( m_queueMutex );

    m_queue.clear();

    this->Replicator::ReplicaClear();
}


//
// Locked Iterator Accessor
//

template< typename T, typename ReplicateP >
class Queue< T, ReplicateP >::ConstLockedQueue : public Detail::ConstLockedSequence< QueueType >
{
public:
    explicit ConstLockedQueue( const Queue& host )
        : Detail::ConstLockedSequence< QueueType >( host.m_queueMutex, host.m_queue )
    {}
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_QUEUE_H
