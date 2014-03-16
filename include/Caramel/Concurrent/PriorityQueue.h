// Caramel C++ Library - Concurrent Amenity - Priority Queue Header

#ifndef __CARAMEL_CONTURRENT_PRIORITY_QUEUE_H
#define __CARAMEL_CONTURRENT_PRIORITY_QUEUE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Thread/MutexLocks.h>
#include <boost/heap/priority_queue.hpp>
#include <boost/noncopyable.hpp>
#include <functional>


namespace Caramel
{

namespace Concurrent
{

///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Priority Queue
// - Based on boost::heap::priority_queue
//
//   The default compare is std::less, which results in
//   the value with the LARGEST key would be popped first.
//
//   If you want the SMALLEST key popped first, use std::greater in KeyCompare,
//   or use the type alias ReversePriorityQueue.
//

template< typename Key, typename Value, typename KeyCompare = std::less< Key > >
class PriorityQueue : public boost::noncopyable
{
public:

    /// Operations ///

    void Push( const Key& k, const Value& v );

    Bool TryPop( Value& v );


    /// Thread-safe Properties ///

    // Returns false if the queue is empty.
    Bool PeekTopKey( Key& key ) const;


    /// Not Thread-safe Properties ///

    Bool IsEmpty() const { return m_queue.empty(); }


private:

    /// Internal Types ///

    struct Entry
    {
        Key key;
        Value value;

        Entry() {}
        Entry( const Key& k, const Value& v ) : key( k ), value( v ) {}
    };

    struct EntryCompare
    {
        KeyCompare compare;

        Bool operator()( const Entry& lhs, const Entry& rhs ) const { return compare( lhs.key, rhs.key ); }
    };


    /// Data Members ///

    typedef boost::heap::priority_queue<
        Entry, boost::heap::compare< EntryCompare > > QueueType;
    QueueType m_queue;

    mutable std::mutex m_queueMutex;
};


//
// Reverse Priority Queue
// - SMALLEST key would be popped first.
//
//   Example: For a timer queue, the smallest due time should be processed first.
//

template< typename Key, typename Value >
class ReversePriorityQueue : public PriorityQueue< Key, Value, std::greater< Key > >
{};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Key, typename Value, typename KeyCompare >
inline void PriorityQueue< Key, Value, KeyCompare >::Push( const Key& k, const Value& v )
{
    LockGuard lock( m_queueMutex );
    m_queue.push( Entry( k, v ));
}


template< typename Key, typename Value, typename KeyCompare >
inline Bool PriorityQueue< Key, Value, KeyCompare >::TryPop( Value& value )
{
    if ( m_queue.empty() ) { return false; }

    LockGuard lock( m_queueMutex );

    if ( m_queue.empty() ) { return false; }

    value = m_queue.top().value;
    m_queue.pop();

    return true;
}


template< typename Key, typename Value, typename KeyCompare >
inline Bool PriorityQueue< Key, Value, KeyCompare >::PeekTopKey( Key& key ) const
{
    if ( m_queue.empty() ) { return false; }

    LockGuard lock( m_queueMutex );

    if ( m_queue.empty() ) { return false; }

    key = m_queue.top().key;

    return true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONTURRENT_PRIORITY_QUEUE_H
