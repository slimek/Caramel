// Caramel C++ Library - Concurrent Amenity - Flat Set Header

#ifndef __CARAMEL_CONCURRENT_FLAT_SET_H
#define __CARAMEL_CONCURRENT_FLAT_SET_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Concurrent/Detail/BasicSet.h>
#include <Caramel/Concurrent/ReplicatePolicies.h>
#include <boost/container/flat_set.hpp>


namespace Caramel
{

namespace Concurrent
{

///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Flat Set
//

template< typename Key, typename ReplicatePolicy = ReplicateNothing >
class FlatSet : public Detail::BasicSet< boost::container::flat_set< Key >, ReplicatePolicy >
{
};


//
// Convenient Alias
//

template< typename Key >
class FlatSetWithSnapshot
    : public Detail::BasicSet< boost::container::flat_set< Key >, ReplicateSnapshot >
{
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_FLAT_SET_H
