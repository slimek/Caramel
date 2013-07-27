// Caramel C++ Library - Chrono Facility - Steady Clock Header

#ifndef __CARAMEL_CHRONO_STEADY_CLOCK_H
#define __CARAMEL_CHRONO_STEADY_CLOCK_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Chrono/Detail/SteadyClockCore.h>
#include <chrono>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Steady Clock
// - Default time unit is 1 second, i.e. ratio< 1 >.
//
//   USAGE:
//     Here are some common typedefs:
//
//     typedef SteadyClock< Float >              SecondClock;
//     typedef SteadyClock< Uint32, std::milli > TickClock;    // milliseconds
//

template< typename ValueType, typename Ratio = std::ratio< 1 > >
class SteadyClock
{
    typedef std::chrono::steady_clock ClockType;
    typedef ClockType::time_point TimePoint;

    typedef std::chrono::duration< ValueType, Ratio > Duration;

public:

    SteadyClock();

    void Reset();

    //
    // Total Elapsed
    // - The duration from the clock is created/reseted until now.
    //
    ValueType GetTotalElapsed() const;
    
    //
    // Delta
    // - Call Delta() successively to get differences of time.
    //
    ValueType Delta();
    
    //
    // Now
    // - A convenient wrapper for the std::steady_clock.
    //
    static ValueType Now();


private:
    TimePoint m_clockStart;
    TimePoint m_intervalStart;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename ValueType, typename Ratio >
inline SteadyClock< ValueType, Ratio >::SteadyClock()
{
    this->Reset();
}


template< typename ValueType, typename Ratio >
inline void SteadyClock< ValueType, Ratio >::Reset()
{
    m_clockStart = m_intervalStart = ClockType::now();
}


template< typename ValueType, typename Ratio >
inline ValueType SteadyClock< ValueType, Ratio >::GetTotalElapsed() const
{
    return std::chrono::duration_cast< Duration >( ClockType::now() - m_clockStart ).count();
}


template< typename ValueType, typename Ratio >
inline ValueType SteadyClock< ValueType, Ratio >::Delta()
{
    const TimePoint now = ClockType::now();
    const Duration delta = std::chrono::duration_cast< Duration >( now - m_intervalStart );
    m_intervalStart = now;
    return delta.count();
}


template< typename ValueType, typename Ratio >
inline ValueType SteadyClock< ValueType, Ratio >::Now()
{
    return std::chrono::duration_cast< Duration >(
        ClockType::now() - Detail::SteadyClockCore::Epoch() ).count();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_STEADY_CLOCK_H
