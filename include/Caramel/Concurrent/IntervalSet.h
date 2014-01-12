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
//   Interval Bound Types:
//     Right Open : [ min, upper )
//     Closed : [ min, max ]
//

template< typename Key >
class IntervalSet : public boost::noncopyable
{
public:

    /// Operations ///

    //
    // Insertion
    // - Return false if it collides with existing intervals.
    //

    Bool Insert( const Key& k );

    Bool InsertRightOpen( const Key& min, const Key& upper );
    Bool InsertClosed   ( const Key& min, const Key& max );


    /// Accessors ///

    Bool Contains( const Key& k ) const;

    Bool ContainsRightOpen( const Key& min, const Key& upper ) const;
    Bool ContainsClosed   ( const Key& min, const Key& max )   const;

    Bool IntersectsRightOpen( const Key& min, const Key& upper ) const;
    Bool IntersectsClosed   ( const Key& min, const Key& max )   const;


private:
    
    /// Locked Accessors ///

    Bool LockedContains( const Key& k ) const;

    Bool LockedIntersectsRightOpen( const Key& min, const Key& upper ) const;
    Bool LockedIntersectsClosed   ( const Key& min, const Key& max )   const;


    /// Data Members ///

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
inline Bool IntervalSet< Key >::Insert( const Key& k )
{
    auto ulock = UniqueLock( m_mutex );
    if ( this->LockedContains( k )) { return false; }
    m_set.insert( k );
    return true;
}


template< typename Key >
inline Bool IntervalSet< Key >::InsertRightOpen( const Key& min, const Key& upper )
{
    auto ulock = UniqueLock( m_mutex );
    const Bool overlapped = this->LockedIntersectsRightOpen( min, upper );
    m_set.insert( SegmentType::right_open( min, upper ));
    return ! overlapped;
}


template< typename Key >
inline Bool IntervalSet< Key >::InsertClosed( const Key& min, const Key& max )
{
    auto ulock = UniqueLock( m_mutex );
    const Bool overlapped = this->LockedIntersectsClosed( min, max );
    m_set.insert( SegmentType::closed( min, max ));
    return ! overlapped;
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


template< typename Key >
inline Bool IntervalSet< Key >::ContainsRightOpen( const Key& min, const Key& upper ) const
{
    auto ulock = UniqueLock( m_mutex );
    return boost::icl::contains( m_set, SegmentType::right_open( min, upper ));
}


template< typename Key >
inline Bool IntervalSet< Key >::ContainsClosed( const Key& min, const Key& max ) const
{
    auto ulock = UniqueLock( m_mutex );
    return boost::icl::contains( m_set, SegmentType::closed( min, max ));
}


template< typename Key >
inline Bool IntervalSet< Key >::IntersectsRightOpen( const Key& min, const Key& upper ) const
{
    auto ulock = UniqueLock( m_mutex );
    return boost::icl::intersects( m_set, SegmentType::right_open( min, upper ));
}


template< typename Key >
inline Bool IntervalSet< Key >::IntersectsClosed( const Key& min, const Key& max ) const
{
    auto ulock = UniqueLock( m_mutex );
    return boost::icl::intersects( m_set, SegmentType::closed( min, max ));
}


//
// Locked Accessors
//

template< typename Key >
inline Bool IntervalSet< Key >::LockedContains( const Key& k ) const
{
    return boost::icl::contains( m_set, k );
}


template< typename Key >
inline Bool IntervalSet< Key >::LockedIntersectsRightOpen( const Key& min, const Key& upper ) const
{
    return boost::icl::intersects( m_set, SegmentType::right_open( min, upper ));
}


template< typename Key >
inline Bool IntervalSet< Key >::LockedIntersectsClosed( const Key& min, const Key& max ) const
{
    return boost::icl::intersects( m_set, SegmentType::closed( min, max ));
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_INTERVAL_SET_H
