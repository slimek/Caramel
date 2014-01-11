// Caramel C++ Library - Concurrent Amenity - Interval Set Header

#ifndef __CARAMEL_CONCURRENT_INTERVAL_SET_H
#define __CARAMEL_CONCURRENT_INTERVAL_SET_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Thread/MutexLocks.h>
#include <boost/icl/interval_set.hpp>
#include <boost/noncopyable.hpp>


namespace Caramel
{

namespace Concurrent
{

///////////////////////////////////////////////////////////////////////////////
//
// Interval Set
// - Based on Boost.Icl ( Interval Container Library )
//

template< typename Key >
class IntervalSet : public boost::noncopyable
{
public:

    /// Operations ///

    void Add( const Key& k );

    // Right Open : [ min, upper )
    void AddRightOpen( const Key& min, const Key& upper );

    // Closed : [ min, max ]
    void AddClosed( const Key& min, const Key& max );


    /// Accessors ///

    Bool Contains( const Key& k ) const;


private:
    
    typedef boost::icl::interval_set< Key > SetType;
    SetType m_set;

    mutable std::mutex m_mutex;

    typedef typename SetType::segment_type SegmentType;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Operations
//

template< typename Key >
inline void IntervalSet< Key >::Add( const Key& k )
{
    auto ulock = UniqueLock( m_mutex );
    m_set.add( k );
}


template< typename Key >
inline void IntervalSet< Key >::AddRightOpen( const Key& min, const Key& upper )
{
    auto ulock = UniqueLock( m_mutex );
    m_set.add( SegmentType::right_open( min, upper ));
}


template< typename Key >
inline void IntervalSet< Key >::AddClosed( const Key& min, const Key& max )
{
    auto ulock = UniqueLock( m_mutex );
    m_set.add( SegmentType::closed( min, max ));
}


//
// Accessors
//

template< typename Key >
inline Bool IntervalSet< Key >::Contains( const Key& k ) const
{
    auto ulock = UniqueLock( m_mutex );
    return boost::icl::contains( m_set, k );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_INTERVAL_SET_H
