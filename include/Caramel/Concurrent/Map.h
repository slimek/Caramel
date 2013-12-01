// Caramel C++ Library - Concurrent Amenity - Map Header

#ifndef __CARAMEL_CONCURRENT_MAP_H
#define __CARAMEL_CONCURRENT_MAP_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Concurrent/Detail/BasicMap.h>
#include <Caramel/Concurrent/ReplicatePolicies.h>
#include <map>


namespace Caramel
{

namespace Concurrent
{

///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Map
//
// NOTE: The ( Key, Value ) naming convention is belong to .NET Framework,
//       not STL/Boost style.
//

template< typename Key, typename Value, typename ReplicatePolicy = ReplicateNothing >
class Map : public Detail::BasicMap< std::map< Key, Value >, ReplicatePolicy >
{
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_MAP_H
