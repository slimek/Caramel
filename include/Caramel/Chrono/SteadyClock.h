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

    typedef std::chrono::duration< ValueType, Ratio > DurationType;

public:

    SteadyClock();

    void Reset();


    typedef ValueType ValueType;

    //
    // Duration
    // - The duration from the clock is created/reseted until now.
    //
    ValueType Duration() const;
    
    //
    // Slice
    // - Get a slice of time :
    //   Return the Duration() and Reset() this clock.
    //
    ValueType Slice();
    
    //
    // Now
    // - A convenient wrapper for the std::steady_clock::now.
    //   Returns a monotolic time.
    //
    static ValueType Now();


private:
    TimePoint m_markTime;
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
    m_markTime = ClockType::now();
}


template< typename ValueType, typename Ratio >
inline ValueType SteadyClock< ValueType, Ratio >::Duration() const
{
    return std::chrono::duration_cast< DurationType >( ClockType::now() - m_markTime ).count();
}


template< typename ValueType, typename Ratio >
inline ValueType SteadyClock< ValueType, Ratio >::Slice()
{
    // This function is equivalent to Duration() then Reset(),
    // but you must use the same now in both functions.

    const TimePoint now = ClockType::now();
    const DurationType delta = std::chrono::duration_cast< DurationType >( now - m_markTime );
    m_markTime = now;
    return delta.count();
}


template< typename ValueType, typename Ratio >
inline ValueType SteadyClock< ValueType, Ratio >::Now()
{
    return std::chrono::duration_cast< DurationType >(
        ClockType::now() - Detail::SteadyClockCore::Epoch() ).count();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_STEADY_CLOCK_H
