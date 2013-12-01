// Caramel C++ Library - Chrono Amenity - Steady Clock Header

#ifndef __CARAMEL_CHRONO_STEADY_CLOCK_H
#define __CARAMEL_CHRONO_STEADY_CLOCK_H
#pragma once

#include <Caramel/Caramel.h>
#include <boost/chrono.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Steady Clock
// - Because VC++ 2012/2013 steady_clock is NOT steady (derived from system_clock),
//   We preferred Boost.Chrono implementation.
//

template< typename DurationT, typename TimePointT >
class SteadyClock
{
    typedef boost::chrono::steady_clock ClockType;

public:

    typedef DurationT  Duration;
    typedef TimePointT TimePoint;


    SteadyClock();

    void Reset();


    // The duration from the clock created/reseted to now.
    Duration Elapsed() const;

    // Get a slice of time :
    // Returns the Elapsed() and then Reset() this clock.
    Duration Slice();

    // A convenient wrapper for std::steady_clock::now.
    static TimePoint Now();

    // Returns duration since the clock's epoch.
    // - In Win32 it is since system started.
    static Duration SinceEpoch();


private:

    TimePoint m_markTime;

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename DurationT, typename TimePointT >
inline SteadyClock< DurationT, TimePointT >::SteadyClock()
{
    this->Reset();
}


template< typename DurationT, typename TimePointT >
inline void SteadyClock< DurationT, TimePointT >::Reset()
{
    m_markTime = SteadyClock::Now();
}


template< typename DurationT, typename TimePointT >
inline DurationT SteadyClock< DurationT, TimePointT >::Elapsed() const
{
    return DurationT( SteadyClock::Now() - m_markTime );
}


template< typename DurationT, typename TimePointT >
inline DurationT SteadyClock< DurationT, TimePointT >::Slice()
{
    // This function is equivalent to Elapsed() then Reset(),
    // but you must use the same now in both functions.

    const TimePoint now = SteadyClock::Now();
    const Duration delta = now - m_markTime;
    m_markTime = now;
    return delta;
}


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
