// Caramel C++ Library - Chrono Facility - Steady Clock Header

#ifndef __CARAMEL_CHRONO_STEADY_CLOCK_H
#define __CARAMEL_CHRONO_STEADY_CLOCK_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Chrono/Detail/SteadyClockCore.h>
#include <chrono>
#include <limits>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Steady Clock
// - Default time unit is 1 second, i.e. ratio< 1 >.
//

template< typename UnitT, typename Ratio = std::ratio< 1 > >
class SteadyClock
{
    typedef std::chrono::steady_clock ClockType;
    typedef ClockType::time_point TimePoint;

    typedef std::chrono::duration< UnitT, Ratio > DurationType;

public:

    SteadyClock();

    void Reset();


    typedef UnitT UnitType;

    //
    // Duration
    // - The duration from the clock is created/reseted until now.
    //
    UnitType Duration() const;
    
    //
    // Slice
    // - Get a slice of time :
    //   Return the Duration() and Reset() this clock.
    //
    UnitType Slice();
    
    //
    // Now
    // - A convenient wrapper for the std::steady_clock::now.
    //   Returns a monotolic time.
    //
    static UnitType Now();

    //
    // Max Value
    // - Depends on the unit type.
    //
    static UnitType MaxValue();


private:
    TimePoint m_markTime;
};


/// Common Typedefs ///

typedef SteadyClock< Double >             SecondClock;
typedef SteadyClock< Uint64, std::milli > TickClock;    // in milliseconds


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
    m_markTime = ClockType::now();
}


template< typename UnitT, typename Ratio >
inline UnitT SteadyClock< UnitT, Ratio >::Duration() const
{
    return std::chrono::duration_cast< DurationType >( ClockType::now() - m_markTime ).count();
}


template< typename UnitT, typename Ratio >
inline UnitT SteadyClock< UnitT, Ratio >::Slice()
{
    // This function is equivalent to Duration() then Reset(),
    // but you must use the same now in both functions.

    const TimePoint now = ClockType::now();
    const DurationType delta = std::chrono::duration_cast< DurationType >( now - m_markTime );
    m_markTime = now;
    return delta.count();
}


template< typename UnitT, typename Ratio >
inline UnitT SteadyClock< UnitT, Ratio >::Now()
{
    return std::chrono::duration_cast< DurationType >(
        ClockType::now() - Detail::SteadyClockCore::Epoch() ).count();
}


template< typename UnitT, typename Ratio >
inline UnitT SteadyClock< UnitT, Ratio >::MaxValue()
{
    return std::numeric_limits< UnitT >::max();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_STEADY_CLOCK_H
