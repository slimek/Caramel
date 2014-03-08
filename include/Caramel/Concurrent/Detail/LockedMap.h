// Caramel C++ Library - Concurrent Amenity - Detail - Locked Map Header

#ifndef __CARAMEL_CONCURRENT_DETAIL_LOCKED_MAP_H
#define __CARAMEL_CONCURRENT_DETAIL_LOCKED_MAP_H
#pragma once

#include <Caramel/Caramel.h>
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
// Const Locked Map
//
// NOTE: The ( Key, Value ) naming convention is belong to .NET Framework,
//       not STL/Boost style.
//

template< typename MapType >
class ConstLockedMap : public boost::noncopyable
{
public:

    ConstLockedMap( std::mutex& mutex, const MapType& map );


    /// Properties ///

    Bool IsEmpty() const { return m_constMap.empty(); }
    Uint Size()    const { return static_cast< Uint >( m_constMap.size() ); }


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
// Implementation
//

template< typename MapT >
ConstLockedMap< MapT >::ConstLockedMap( std::mutex& mutex, const MapT& map )
    : m_lock( mutex )
    , m_constMap( map )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_DETAIL_LOCKED_MAP_H
