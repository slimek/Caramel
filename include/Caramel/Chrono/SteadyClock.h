// Caramel C++ Library - Chrono Amenity - Steady Clock Header

#ifndef __CARAMEL_CHRONO_STEADY_CLOCK_H
#define __CARAMEL_CHRONO_STEADY_CLOCK_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <chrono>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Steady Clock
// - Default time unit is 1 second, i.e. ratio< 1 >.
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

    ValueType GetTotalElapsed() const;

    
    //
    // Delta
    // - Call Delta() successively to get differences of time.
    //
    ValueType Delta();
    

private:
    TimePoint m_clockStart;
    TimePoint m_intervalStart;
};


//
// Implementation
//

template< typename ValueType, typename Ratio >
SteadyClock< ValueType, Ratio >::SteadyClock()
{
    this->Reset();
}


template< typename ValueType, typename Ratio >
void SteadyClock< ValueType, Ratio >::Reset()
{
    m_clockStart = m_intervalStart = ClockType::now();
}


template< typename ValueType, typename Ratio >
ValueType SteadyClock< ValueType, Ratio >::GetTotalElapsed() const
{
    return Duration( ClockType::now() - m_clockStart ).count();
}


template< typename ValueType, typename Ratio >
ValueType SteadyClock< ValueType, Ratio >::Delta()
{
    const TimePoint now = ClockType::now();
    const Duration delta = now - m_intervalStart;
    m_intervalStart = now;
    return delta.count();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_STEADY_CLOCK_H
