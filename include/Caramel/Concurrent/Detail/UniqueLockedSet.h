// Caramel C++ Library - Concurrent Amenity - Detail - Unique Locked Set Header

#ifndef __CARAMEL_CONCURRENT_DETAIL_UNIQUE_LOCKED_SET_H
#define __CARAMEL_CONCURRENT_DETAIL_UNIQUE_LOCKED_SET_H
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
// Unique Locked Set
//

template< typename SetType >
class UniqueLockedSet : public boost::noncopyable
{
public:

    UniqueLockedSet( std::mutex& mutex, SetType& set );


    /// Properties ///

    Bool IsEmpty() const { return m_set.empty(); }
    Uint Size()    const { return static_cast< Uint >( m_set.size() ); }


    /// Accessors ///

    typedef typename SetType::key_type Key, KeyType;

    Bool Contains( const Key& k ) const;


    typedef typename SetType::const_iterator ConstIterator;

    ConstIterator Begin() const { return m_set.begin(); }
    ConstIterator End()   const { return m_set.end(); }

    
    // Compatible with STL/Boost

    typedef typename SetType::const_iterator const_iterator;

    const_iterator begin() const { return m_set.begin(); }
    const_iterator end()   const { return m_set.end(); }


private:

    /// Data Members ///

    std::unique_lock< std::mutex > m_lock;
    SetType& m_set;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename SetT >
UniqueLockedSet< SetT >::UniqueLockedSet( std::mutex& mutex, SetT& set )
    : m_lock( mutex )
    , m_set( set )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_DETAIL_UNIQUE_LOCKED_SET_H
