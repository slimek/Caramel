// Caramel C++ Library - Concurrent Amenity - Basic Map Header

#ifndef __CARAMEL_CONCURRENT_BASIC_MAP_H
#define __CARAMEL_CONCURRENT_BASIC_MAP_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Thread/MutexLocks.h>
#include <boost/noncopyable.hpp>
#include <mutex>


namespace Caramel
{

namespace Concurrent
{

///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Basic Map
// - Provides thread-safe protection for STL/Boost map-like containers.
//

template< typename MapType, typename ReplicatePolicy >
class BasicMap : public boost::noncopyable
{
public:

    typedef typename MapType::key_type    Key,   KeyType;
    typedef typename MapType::mapped_type Value, ValueType;

    typedef typename ReplicatePolicy::template Dictionary< Key, Value > Replicator;


    /// Properties ///

    Bool IsEmpty() const { return m_map.empty(); }
    Uint Size()    const { return m_map.size(); }


    /// Accessors ///

    Bool Contains( const Key& k ) const;
    Bool Find( const Key& k, Value& v ) const;


    /// Modifiers ///
    
    Bool Insert( const Key& k, const Value& v );


private:

    /// Data Members ///

    MapType m_map;
    std::mutex m_mapMutex;

    Replicator m_replicator;
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
    return m_mpa.end() != m_map.find( k );
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
        m_replicator.Insert( k, v );
    }

    return inserted;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_BASIC_MAP_H
