// Caramel C++ Library - Concurrent Amenity - Detail - Locked Interval Set Header

#ifndef __CARAMEL_CONCURRENT_DETAIL_LOCKED_INTERVAL_SET_H
#define __CARAMEL_CONCURRENT_DETAIL_LOCKED_INTERVAL_SET_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <boost/icl/interval_set.hpp>
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
// Const Locked Interval Set
// - For supporting Snapshot.
//

template< typename Key >
class ConstLockedIntervalSet : public boost::noncopyable
{
    typedef boost::icl::interval_set< Key > SetType;

public:

    ConstLockedIntervalSet( std::mutex& mutex, const SetType& set );


    /// Properties ///

    Bool IsEmpty() const { return m_constSet.empty(); }

    //
    // NOTES:
    // - interval_set::size() returns how may elements in the container.
    //   For example, a [1,3]-[5,7] set would returns 6.
    //   But our snapshot are based on interals, not elements.
    //
    Usize Size() const { return m_constSet.iterative_size(); }


    /// Accessors ///

    typedef typename SetType::const_iterator ConstIterator;

    ConstIterator Begin() const { return m_constSet.begin(); }
    ConstIterator End()   const { return m_constSet.end(); }


private:

    std::lock_guard< std::mutex > m_lock;
    const SetType& m_constSet;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Key >
inline ConstLockedIntervalSet< Key >::ConstLockedIntervalSet( std::mutex& mutex, const SetType& set )
    : m_lock( mutex )
    , m_constSet( set )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_DETAIL_LOCKED_INTERVAL_SET_H
