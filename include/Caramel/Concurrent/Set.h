// Caramel C++ Library - Concurrent Amenity - Set Header

#ifndef __CARAMEL_CONCURRENT_SET_H
#define __CARAMEL_CONCURRENT_SET_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Concurrent/Detail/BasicSet.h>
#include <Caramel/Concurrent/ReplicatePolicies.h>
#include <set>


namespace Caramel
{

namespace Concurrent
{

///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Set
//

template< typename Key, typename ReplicatePolicy = ReplicateNothing >
class Set : public Detail::BasicSet< std::set< Key >, ReplicatePolicy >
{
};


//
// Convenient Alias
//

template< typename Key >
class SetWithSnapshot : public Detail::BasicSet< std::set< Key >, ReplicateSnapshot >
{
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_SET_H
