// Caramel C++ Library - Concurrent Amenity - Detail - Dictionary Snapshot Header

#ifndef __CARAMEL_CONCURRENT_DETAIL_DICTIONARY_SNAPSHOT_H
#define __CARAMEL_CONCURRENT_DETAIL_DICTIONARY_SNAPSHOT_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
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
// Dictionary Snapshot
// - When a snapshot is required, build it if :
//   1. It doesn't exist.
//   2. The container has been modified.
//

template< typename Derived, typename Key, typename Value >
class DictionarySnapshot
{
public:

    typedef ConstSharedArray< Value > ValuesSnapshot;

    typedef std::pair< Key, Value > PairType;
    typedef ConstSharedArray< PairType > PairsSnapshot;

    DictionarySnapshot();

    /// Accessors ///

    ValuesSnapshot GetValuesSnapshot() const;
    PairsSnapshot  GetPairsSnapshot()  const;


protected:

    /// Operations ///

    void ReplicaAdd( const Key& k, const Value& v );
    void ReplicaRemove( const Key& k );
    void ReplicaClear();


private:

    mutable Bool m_valuesModified;
    mutable ValuesSnapshot m_valuesSnapshot;

    mutable Bool m_pairsModified;
    mutable PairsSnapshot m_pairsSnapshot;

    mutable std::mutex m_snapshotMutex;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Derived, typename Key, typename Value >
inline DictionarySnapshot< Derived, Key, Value >::DictionarySnapshot()
    : m_valuesModified( false )
    , m_pairsModified( false )
{
}


template< typename Derived, typename Key, typename Value >
inline void DictionarySnapshot< Derived, Key, Value >::ReplicaAdd( const Key&, const Value& )
{
    LockGuard lock( m_snapshotMutex );
    m_valuesModified = true;
    m_pairsModified  = true;
}


template< typename Derived, typename Key, typename Value >
inline void DictionarySnapshot< Derived, Key, Value >::ReplicaRemove( const Key& )
{
    this->ReplicaClear();
}


template< typename Derived, typename Key, typename Value >
inline void DictionarySnapshot< Derived, Key, Value >::ReplicaClear()
{
    LockGuard lock( m_snapshotMutex );
    m_valuesModified = true;
    m_pairsModified  = true;

    if ( ! m_valuesSnapshot.IsEmpty() )
    {
        m_valuesSnapshot = SharedArray< Value >();
    }

    if ( ! m_pairsSnapshot.IsEmpty() )
    {
        m_pairsSnapshot = SharedArray< PairType >();
    }
}


template< typename Derived, typename Key, typename Value >
inline auto DictionarySnapshot< Derived, Key, Value >::GetValuesSnapshot() const -> ValuesSnapshot
{
    {
        LockGuard lock( m_snapshotMutex );
        if ( ! m_valuesModified )
        {
            return m_valuesSnapshot;
        }
    }

    /// Rebuild the snapshot ///

    const Derived& derived = static_cast< const Derived& >( *this );

    // ATTENTION: Always lock the derived before the snapshot mutex !!

    typename Derived::ConstLockedDictionary lockedDerived( derived );
    LockGuard lock( m_snapshotMutex );

    if ( ! m_valuesModified )
    {
        // The snapshot has been rebuilt by another thread.
        return m_valuesSnapshot;
    }

    SharedArray< Value > newValues( lockedDerived.Size() );
    Uint index = 0;
    for ( auto pair : lockedDerived )
    {
        newValues[index] = pair.second;
        ++ index;
    }

    m_valuesSnapshot = newValues;
    m_valuesModified = false;

    return m_valuesSnapshot;
}


template< typename Derived, typename Key, typename Value >
inline auto DictionarySnapshot< Derived, Key, Value >::GetPairsSnapshot() const -> PairsSnapshot
{
    {
        LockGuard lock( m_snapshotMutex );
        if ( ! m_pairsModified )
        {
            return m_pairsSnapshot;
        }
    }

    /// Rebuild the snapshot ///

    const Derived& derived = static_cast< const Derived& >( *this );

    // ATTENTION: Always lock the derived before the snapshot mutex !!

    typename Derived::ConstLockedDictionary lockedDerived( derived );
    LockGuard lock( m_snapshotMutex );

    if ( ! m_pairsModified )
    {
        // The snapshot has been rebuilt by another thread.
        return m_pairsSnapshot;
    }

    SharedArray< PairType > newPairs( lockedDerived.Size() );
    Uint index = 0;
    for ( auto pair : lockedDerived )
    {
        newPairs[index] = pair;
        ++ index;
    }

    m_pairsSnapshot = newPairs;
    m_pairsModified = false;

    return m_pairsSnapshot;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_DETAIL_DICTIONARY_SNAPSHOT_H
