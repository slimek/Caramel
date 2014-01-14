// Caramel C++ Library - Concurrent Amenity - Basic Set Header

#ifndef __CARAMEL_CONCURRENT_BASIC_SET_H
#define __CARAMEL_CONCURRENT_BASIC_SET_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Thread/MutexLocks.h>
#include <boost/noncopyable.hpp>
#include <mutex>


namespace Caramel
{

namespace Concurrent
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Basic Set
// - Provides thread-safe protection for STL/Boost set-like containers.
//

template< typename SetType, typename ReplicatePolicy >
class BasicSet : public ReplicatePolicy::template Collection< typename SetType::key_type >
               , public boost::noncopyable
{
public:

    typedef typename SetType::key_type Key, KeyType;

    typedef typename ReplicatePolicy::template Collection< Key > Replicator;


    /// Properties ///

    Bool IsEmpty() const { return m_set.empty(); }
    Uint Size()    const { return static_cast< Uint >( m_set.size() ); }


    /// Accessors ///

    Bool Contains( const Key& k ) const;


    /// Modifiers ///

    Bool Insert( const Key& k );


private:

    /// Data Members ///

    SetType m_set;
    mutable std::mutex m_setMutex;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Accessors
//

template< typename SetT, typename ReplicateP >
Bool BasicSet< SetT, ReplicateP >::Contains( const Key& k ) const
{
    auto ulock = UniqueLock( m_setMutex );
    return m_set.end() != m_set.find( k );
}


//
// Modifiers
//

template< typename SetT, typename ReplicateP >
Bool BasicSet< SetT, ReplicateP >::Insert( const Key& k )
{
    auto ulock = UniqueLock( m_setMutex );

    const Bool inserted = m_set.insert( k ).second;

    if ( inserted )
    {
        this->Replicator::Add( k );
    }

    return inserted;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_BASIC_SET_H
