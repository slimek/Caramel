// Caramel C++ Library - Concurrent Amenity - Basic Set Header

#ifndef __CARAMEL_CONCURRENT_BASIC_SET_H
#define __CARAMEL_CONCURRENT_BASIC_SET_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Thread/MutexLocks.h>
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
// Concurrent Basic Set
// - Provides thread-safe protection for STL/Boost set-like containers.
//

template< typename SetType, typename ReplicatePolicy >
class BasicSet : public ReplicatePolicy::template Collection< typename SetType::key_type >
               , public boost::noncopyable
{
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Concurrent

} // namespace Caramel

#endif // __CARAMEL_CONCURRENT_BASIC_SET_H
