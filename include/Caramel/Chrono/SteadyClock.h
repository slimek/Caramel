// Caramel C++ Library - Chrono Amenity - Steady Clock Header

#ifndef __CARAMEL_CHRONO_STEADY_CLOCK_H
#define __CARAMEL_CHRONO_STEADY_CLOCK_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <boost/chrono.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Steady Clock
// - Because VC++ 2012/2013 steady_clock is NOT steady (derived from system_clock),
//   We preferred Boost.Chrono implementation.
//

template< typename UnitT, typename Ratio >
class SteadyClock
{
    typedef boost::chrono::steady_clock ClockType;

public:

    SteadyClock();

    void Reset();


    //
    // Typedefs
    //

    typedef UnitT UnitType;
    typedef boost::chrono::duration< UnitT, Ratio > Duration;
    typedef boost::chrono::time_point< ClockType, Duration > TimePoint;


    //
    // Elapsed
    // - The duration from the clock is created/reseted until now.
    //
    Duration Elapsed() const;
    
    //
    // Slice
    // - Get a slice of time :
    //   Return the Duration() and Reset() this clock.
    //
    Duration Slice();
    
    //
    // Now
    // - A convenient wrapper for the std::steady_clock::now.
    //
    static TimePoint Now();


private:
    TimePoint m_markTime;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename UnitT, typename Ratio >
inline SteadyClock< UnitT, Ratio >::SteadyClock()
{
    this->Reset();
}


template< typename UnitT, typename Ratio >
inline void SteadyClock< UnitT, Ratio >::Reset()
{
    m_markTime = SteadyClock::Now();
}


template< typename UnitT, typename Ratio >
inline auto SteadyClock< UnitT, Ratio >::Elapsed() const -> Duration
{
    return SteadyClock::Now() - m_markTime;
}


template< typename UnitT, typename Ratio >
inline auto SteadyClock< UnitT, Ratio >::Slice() -> Duration
{
    // This function is equivalent to Elapsed() then Reset(),
    // but you must use the same now in both functions.

    const TimePoint now = SteadyClock::Now();
    const Duration delta = now - m_markTime;
    m_markTime = now;
    return delta;
}


template< typename UnitT, typename Ratio >
inline auto SteadyClock< UnitT, Ratio >::Now() -> TimePoint
{
    return boost::chrono::time_point_cast< Duration >( ClockType::now() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_STEADY_CLOCK_H
