// Caramel C++ Library - Concurrent Amenity - Detail - Locked Set Header

#ifndef __CARAMEL_CONCURRENT_DETAIL_LOCKED_SET_H
#define __CARAMEL_CONCURRENT_DETAIL_LOCKED_SET_H
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
// Const Locked Set
//

template< typename SetType >
class ConstLockedSet : public boost::noncopyable
{
public:
    
    ConstLockedSet( std::mutex& mutex, const SetType& set );


    /// Properties ///

    Bool IsEmpty() const { return m_constSet.empty(); }
    Uint Size()    const { return static_cast< Uint >( m_constSet.size() ); }


    /// Accessors ///

    typedef typename SetType::key_type Key, KeyType;

    Bool Contains( const Key& k ) const;


    typedef typename SetType::const_iterator ConstIterator;

    ConstIterator Begin() const { return m_constSet.begin(); }
    ConstIterator End()   const { return m_constSet.end(); }

    
    // Compatible with STL/Boost

    typedef typename SetType::const_iterator const_iterator;

    const_iterator begin() const { return m_constSet.begin(); }
    const_iterator end()   const { return m_constSet.end(); }


private:

    std::lock_guard< std::mutex > m_lock;
    const SetType& m_constSet;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename SetT >
ConstLockedSet< SetT >::ConstLockedSet( std::mutex& mutex, const SetT& set )
    : m_lock( mutex )
    , m_constSet( set )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_DETAIL_LOCKED_SET_H
