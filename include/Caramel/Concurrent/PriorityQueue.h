// Caramel C++ Library - Concurrent Amenity - Priority Queue Header

#ifndef __CARAMEL_CONTURRENT_PRIORITY_QUEUE_H
#define __CARAMEL_CONTURRENT_PRIORITY_QUEUE_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Thread/MutexLocks.h>
#include <boost/heap/priority_queue.hpp>
#include <boost/noncopyable.hpp>


namespace Caramel
{

namespace Concurrent
{

///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Priority Queue
// - Based on boost::heap::priority_queue
//   The value with smallest key would be popped first.
//

template< typename Key, typename Value >
class PriorityQueue : public boost::noncopyable
{
public:

    void Push( const Key& k, const Value& v );


private:

    struct Entry
    {
        Key key;
        Value value;

        Entry();
        Entry( const Key& k, const Value& v );

        Bool operator<( const Entry& rhs ) const;
    };

    typedef boost::heap::priority_queue< Entry > QueueType;
    QueueType m_queue;

    std::mutex m_queueMutex;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Key, typename Value >
inline void PriorityQueue< Key, Value >::Push( const Key& k, const Value& v )
{
    auto ulock = UniqueLock( m_queueMutex );

    m_queue.push( Entry( k, v ));
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONTURRENT_PRIORITY_QUEUE_H
