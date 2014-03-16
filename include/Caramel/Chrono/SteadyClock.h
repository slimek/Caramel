// Caramel C++ Library - Chrono Amenity - Steady Clock Header

#ifndef __CARAMEL_CHRONO_STEADY_CLOCK_H
#define __CARAMEL_CHRONO_STEADY_CLOCK_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <boost/chrono.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Steady Clock
// - Because VC++ 2012/2013 steady_clock is NOT steady (derived from system_clock),
//   we preferred Boost.Chrono implementation.
//

template< typename DurationT, typename TimePointT >
class SteadyClock
{
    typedef boost::chrono::steady_clock ClockType;

public:

    typedef DurationT  Duration;
    typedef TimePointT TimePoint;


    // A convenient wrapper for std::steady_clock::now.
    static TimePoint Now();

    // Returns duration since the clock's epoch.
    // - In Win32 it is since system started.
    static Duration SinceEpoch();
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename DurationT, typename TimePointT >
inline TimePointT SteadyClock< DurationT, TimePointT >::Now()
{
    return boost::chrono::time_point_cast< typename TimePoint::Duration >( ClockType::now() );
}


template< typename DurationT, typename TimePointT >
inline DurationT SteadyClock< DurationT, TimePointT >::SinceEpoch()
{
    return Duration( Now().time_since_epoch() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_STEADY_CLOCK_H
