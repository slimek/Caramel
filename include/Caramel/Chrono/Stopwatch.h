// Caramel C++ Library - Chrono Amenity - Stopwatch Header

#ifndef __CARAMEL_CHRONO_STOPWATCH_H
#define __CARAMEL_CHRONO_STOPWATCH_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Stopwatch
// 
//   Concept of Clock:
//   - Has typedefs of Duration, TimePoint
//     Has static function Now()
//

template< typename Clock >
class Stopwatch
{
public:

    typedef Clock ClockType;

    typedef typename ClockType::Duration  Duration;
    typedef typename ClockType::TimePoint TimePoint;


    Stopwatch();

    void Reset();


    // The duration from the clock created/reseted to now.
    Duration Elapsed() const;

    // Get a slice of time :
    // Returns the Elapsed() and then Reset() this clock.
    Duration Slice();


private:

    // The last time when this watch starts or resets.
    TimePoint m_markTime;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Clock >
inline Stopwatch< Clock >::Stopwatch()
{
    this->Reset();
}


template< typename Clock >
inline void Stopwatch< Clock >::Reset()
{
    m_markTime = Clock::Now();
}


template< typename Clock >
inline auto Stopwatch< Clock >::Elapsed() const -> Duration
{
    return Duration( Clock::Now() - m_markTime );
}


template< typename Clock >
inline auto Stopwatch< Clock >::Slice() -> Duration
{
    // This function is ALMOST equivalent to Elapsed() then Reset(),
    // but here we can use the same now in both functions.

    const TimePoint now = Clock::Now();
    const Duration delta = now - m_markTime;
    m_markTime = now;
    return delta;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_STOPWATCH_H
