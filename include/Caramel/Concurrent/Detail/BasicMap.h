// Caramel C++ Library - Concurrent Amenity - Detail - Basic Map Header

#ifndef __CARAMEL_CONCURRENT_DETAIL_BASIC_MAP_H
#define __CARAMEL_CONCURRENT_DETAIL_BASIC_MAP_H
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
// Concurrent Basic Map
// - Provides thread-safe protection for STL/Boost map-like containers.
//

template< typename MapType, typename ReplicatePolicy >
class BasicMap : public ReplicatePolicy::template Dictionary< typename MapType::key_type, typename MapType::mapped_type >
               , public boost::noncopyable
{
public:

    typedef typename MapType::key_type    Key,   KeyType;
    typedef typename MapType::mapped_type Value, ValueType;

    typedef typename ReplicatePolicy::template Dictionary< Key, Value > Replicator;


    /// Properties ///

    Bool IsEmpty() const { return m_map.empty(); }
    Uint Size()    const { return static_cast< Uint >( m_map.size() ); }


    /// Accessors ///

    Bool Contains( const Key& k ) const;
    Bool Find( const Key& k, Value& v ) const;


    /// Modifiers ///
    
    Bool Insert( const Key& k, const Value& v );


private:

    /// Data Members ///

    MapType m_map;
    mutable std::mutex m_mapMutex;
};


//
// Implementation
//

//
// Accessors
//

template< typename MapT, typename ReplicateP >
Bool BasicMap< MapT, ReplicateP >::Contains( const Key& k ) const
{
    auto ulock = UniqueLock( m_mapMutex );
    return m_map.end() != m_map.find( k );
}


template< typename MapT, typename ReplicateP >
Bool BasicMap< MapT, ReplicateP >::Find( const Key& k, Value& v ) const
{
    auto ulock = UniqueLock( m_mapMutex );

    auto iter = m_map.find( k );
    if ( m_map.end() == iter ) { return false; }
    v = iter->second;
    return true;
}


//
// Modifiers
//

template< typename MapT, typename ReplicateP >
Bool BasicMap< MapT, ReplicateP >::Insert( const Key& k, const Value& v )
{
    auto ulock = UniqueLock( m_mapMutex );

    const Bool inserted = m_map.insert( std::make_pair( k, v )).second;

    if ( inserted )
    {
        this->Replicator::Add( k, v );
    }

    return inserted;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_DETAIL_BASIC_MAP_H
