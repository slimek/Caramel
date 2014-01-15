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


private:

    void ClearSnapshot();
    void BuildSnapshot();

    Bool m_built;
    SnapshotType m_snapshot;

    mutable std::mutex m_buildMutex;
    mutable std::mutex m_snapshotMutex;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Derived, typename Value >
inline CollectionSnapshot< Derived, Value >::CollectionSnapshot()
    : m_built( false )
{
}


template< typename Derived, typename Value >
inline void CollectionSnapshot< Derived, Value >::ReplicaAdd( const Value& v )
{
    this->ClearSnapshot();
}


template< typename Derived, typename Value >
inline void CollectionSnapshot< Derived, Value >::ReplicaRemove( const Value& v )
{
    this->ClearSnapshot();
}


template< typename Derived, typename Value >
inline void CollectionSnapshot< Derived, Value >::ClearSnapshot()
{
    if ( ! m_built ) { return; }

    auto ulock = UniqueLock( m_snapshotMutex );

    if ( ! m_built ) { return; }

    m_snapshot = SharedArray< Value >();
    m_built = false;
}


template< typename Derived, typename Value >
inline auto CollectionSnapshot< Derived, Value >::GetSnapshot() const -> SnapshotType
{
    // TODO: Rebuild snapshot when modified.

    return m_snapshot;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_DETAIL_COLLECTION_SNAPSHOT_H
