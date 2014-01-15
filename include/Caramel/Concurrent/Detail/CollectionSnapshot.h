// Caramel C++ Library - Concurrent Amenity - Detail - Collection Snapshot Header

#ifndef __CARAMEL_CONCURRENT_DETAIL_COLLECTION_SNAPSHOT_H
#define __CARAMEL_CONCURRENT_DETAIL_COLLECTION_SNAPSHOT_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Thread/MutexLocks.h>
#include <Caramel/Value/SharedArray.h>
#include <mutex>


namespace Caramel
{

namespace Concurrent
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Collection Snapshot
// - 1. When the derived container modified, clear the snapshot.
//   2. Build snapshot if it is required and doesn't exist. 
// 

template< typename Derived, typename Value >
class CollectionSnapshot
{
public:

    typedef ConstSharedArray< Value > SnapshotType;

    CollectionSnapshot();

    /// Accessors ///

    SnapshotType GetSnapshot() const;


protected:

    /// Operations ///

    void ReplicaAdd( const Value& v );
    void ReplicaRemove( const Value& v );
    void ReplicaClear();


private:

    mutable Bool m_modified;
    mutable SnapshotType m_snapshot;

    mutable std::mutex m_snapshotMutex;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Derived, typename Value >
inline CollectionSnapshot< Derived, Value >::CollectionSnapshot()
    : m_modified( false )
{
}


template< typename Derived, typename Value >
inline void CollectionSnapshot< Derived, Value >::ReplicaAdd( const Value& v )
{
    auto ulock = UniqueLock( m_snapshotMutex );
    m_modified = true;
}


template< typename Derived, typename Value >
inline void CollectionSnapshot< Derived, Value >::ReplicaRemove( const Value& v )
{
    auto ulock = UniqueLock( m_snapshotMutex );
    m_modified = true;

    if ( ! m_snapshot.IsEmpty() )
    {
        // Clear the snapshot
        m_snapshot = SharedArray< Value >();
    }
}


template< typename Derived, typename Value >
inline auto CollectionSnapshot< Derived, Value >::GetSnapshot() const -> SnapshotType
{
    {
        auto snapshotLock = UniqueLock( m_snapshotMutex );
        if ( ! m_modified )
        {
            return m_snapshot;
        }
    }

    /// Rebuild the snapshot ///

    const Derived& derived = static_cast< const Derived& >( *this );

    // ATTENTION: Always lock the derived mutex before the snapshot mutex !!

    //auto derivedLock = UniqueLock( derived.OriginMutex() );
    auto snapshotLock = UniqueLock( m_snapshotMutex );

    if ( ! m_modified )
    {
        // The Snapshot has been rebuilt by another thread.
        return m_snapshot;
    }

    SharedArray< Value > newSnapshot( derived.Size() );
    //std::copy( derived.OriginBegin(), derived.OriginEnd(), newSnapshot.Begin() );

    m_snapshot = newSnapshot;
    m_modified = false;

    return m_snapshot;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_DETAIL_COLLECTION_SNAPSHOT_H
