// Caramel C++ Library - Concurrent Amenity - Detail - Basic Set Header

#ifndef __CARAMEL_CONCURRENT_DETAIL_BASIC_SET_H
#define __CARAMEL_CONCURRENT_DETAIL_BASIC_SET_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Concurrent/Detail/LockedSet.h>
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
class BasicSet : public ReplicatePolicy::template Collection
                 <
                     BasicSet< SetType, ReplicatePolicy >,
                     typename SetType::key_type
                 >
               , public boost::noncopyable
{
public:

    typedef typename SetType::key_type Key, KeyType;

    typedef typename ReplicatePolicy::template Collection
    <
        BasicSet< SetType, ReplicatePolicy >,
        KeyType
    >
    Replicator;


    /// Properties ///

    Bool IsEmpty() const { return m_set.empty(); }
    Uint Size()    const { return static_cast< Uint >( m_set.size() ); }


    /// Accessors ///

    Bool Contains( const Key& k ) const;


    /// Modifiers ///

    Bool Insert( const Key& k );
    Uint Erase( const Key& k );

    void Clear();


    /// Locked Iterator Accessor ///

    class ConstLockedSet;
    friend class ConstLockedSet;

    // For Replicator
    typedef ConstLockedSet ConstLockedCollection;


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
    LockGuard lock( m_setMutex );
    return m_set.end() != m_set.find( k );
}


//
// Modifiers
//

template< typename SetT, typename ReplicateP >
Bool BasicSet< SetT, ReplicateP >::Insert( const Key& k )
{
    LockGuard lock( m_setMutex );

    const Bool inserted = m_set.insert( k ).second;

    if ( inserted )
    {
        this->Replicator::ReplicaAdd( k );
    }

    return inserted;
}


template< typename SetT, typename ReplicateP >
Uint BasicSet< SetT, ReplicateP >::Erase( const Key& k )
{
    LockGuard lock( m_setMutex );

    const Usize erased = m_set.erase( k );

    if ( 0 < erased )
    {
        this->Replicator::ReplicaRemove( k );
    }

    return static_cast< Uint >( erased );
}


template< typename SetT, typename ReplicateP >
void BasicSet< SetT, ReplicateP >::Clear()
{
    LockGuard lock( m_setMutex );

    if ( ! m_set.empty() )
    {
        m_set.clear();
        this->Replicator::ReplicaClear();
    }
}


//
// Locked Iterator Accessor
//

template< typename SetT, typename ReplicateP >
class BasicSet< SetT, ReplicateP >::ConstLockedSet : public Detail::ConstLockedSet< SetT >
{
public:
    explicit ConstLockedSet( const BasicSet& host )
        : Detail::ConstLockedSet< SetT >( host.m_setMutex, host.m_set )
    {}
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_DETAIL_BASIC_SET_H
