// Caramel C++ Library - Concurrent Amenity - Priority Queue Header

#ifndef __CARAMEL_CONTURRENT_PRIORITY_QUEUE_H
#define __CARAMEL_CONTURRENT_PRIORITY_QUEUE_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Thread/MutexLocks.h>
#include <boost/noncopyable.hpp>

#if defined( CARAMEL_COMPILER_IS_MSVC )
#pragma warning( push )
#pragma warning( disable:4390 )
#include <boost/heap/binomial_heap.hpp>
#pragma warning( pop )
#else
#include <boost/heap/binomial_heap.hpp>
#endif


namespace Caramel
{

namespace Concurrent
{

///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Priority Queue
// - Based on boost::heap::binomial_heap
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

    typedef boost::heap::binomial_heap< Entry > HeapType;
    HeapType m_heap;

    std::mutex m_heapMutex;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Key, typename Value >
inline void PriorityQueue< Key, Value >::Push( const Key& k, const Value& v )
{
    auto ulock = UniqueLock( m_heapMutex );

    m_heap.push( Entry( k, v ));
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONTURRENT_PRIORITY_QUEUE_H
