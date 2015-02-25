// Caramel C++ Library - Concurrent Amenity - Detail - Locked Map Header

#ifndef __CARAMEL_CONCURRENT_DETAIL_LOCKED_MAP_H
#define __CARAMEL_CONCURRENT_DETAIL_LOCKED_MAP_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <boost/noncopyable.hpp>
#include <mutex>


namespace Caramel
{

namespace Concurrent
{

namespace Detail
{

//
// NOTE: The ( Key, Value ) naming convention is belong to .NET Framework,
//       not STL/Boost style.
//

///////////////////////////////////////////////////////////////////////////////
//
// Const Locked Map
//

template< typename MapType >
class ConstLockedMap : public boost::noncopyable
{
public:

    ConstLockedMap( std::mutex& mutex, const MapType& map );


    /// Properties ///

    Bool  IsEmpty() const { return m_constMap.empty(); }
    Usize Size()    const { return m_constMap.size(); }


    /// Accessors ///

    typedef typename MapType::key_type    Key, KeyType;
    typedef typename MapType::mapped_type Value, ValueType;

    Bool Contains( const Key& k ) const;


    typedef typename MapType::const_iterator ConstIterator;

    ConstIterator Begin() const { return m_constMap.begin(); }
    ConstIterator End()   const { return m_constMap.end(); }


    // Compatible with STL/Boost

    typedef typename MapType::const_iterator const_iterator;

    const_iterator begin() const { return m_constMap.begin(); }
    const_iterator end()   const { return m_constMap.end(); }


private:

    std::lock_guard< std::mutex > m_lock;
    const MapType& m_constMap;
};


///////////////////////////////////////////////////////////////////////////////
//
// Locked Map (mutable)
//

template< typename MapType >
class LockedMap : public boost::noncopyable
{
public:

    LockedMap( std::mutex& mutex, MapType& map );


    /// Operations ///

    typedef typename MapType::key_type    Key;
    typedef typename MapType::mapped_type Value;

    void Clear();

    Bool Insert( const Key& k, const Value& v );


private:

    std::lock_guard< std::mutex > m_lock;
    MapType& m_map;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Const Locked Map
//

template< typename MapT >
inline ConstLockedMap< MapT >::ConstLockedMap( std::mutex& mutex, const MapT& map )
    : m_lock( mutex )
    , m_constMap( map )
{
}


//
// Mutable Locked Map
//

template< typename MapT >
inline LockedMap< MapT >::LockedMap( std::mutex& mutex, MapT& map )
    : m_lock( mutex )
    , m_map( map )
{
}


template< typename MapT >
inline void LockedMap< MapT >::Clear()
{
    m_map.clear();
}


template< typename MapT >
inline Bool LockedMap< MapT >::Insert( const Key& k, const Value& v )
{
    return m_map.insert( std::make_pair( k, v )).second;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_DETAIL_LOCKED_MAP_H
