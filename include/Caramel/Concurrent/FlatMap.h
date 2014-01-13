// Caramel C++ Library - Concurrent Amenity - Flat Map Header

#ifndef __CARAMEL_CONCURRENT_FLAT_MAP_H
#define __CARAMEL_CONCURRENT_FLAT_MAP_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Concurrent/Detail/BasicMap.h>
#include <Caramel/Concurrent/ReplicatePolicies.h>
#include <boost/container/flat_map.hpp>


namespace Caramel
{

namespace Concurrent
{

///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Flat Map
// - Based on Boost.Container flat_map, which works as a sorted vector.
//
// NOTE: The ( Key, Value ) naming convention is belong to .NET Framework,
//       not STL/Boost style.
//

template< typename Key, typename Value, typename ReplicatePolicy = ReplicateNothing >
class FlatMap : public Detail::BasicMap< boost::container::flat_map< Key, Value >, ReplicatePolicy >
{
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_FLAT_MAP_H
