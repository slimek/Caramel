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
//   Concept of ClockT:
//   - Has typedefs of Duration, TimePoint
//     Has static function Now()
//

template< typename ClockT >
class Stopwatch
{
public:

    typedef ClockT ClockType;

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

    TimePoint m_markTime;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename ClockT >
inline Stopwatch< ClockT >::Stopwatch()
{
    this->Reset();
}


template< typename ClockT >
inline void Stopwatch< ClockT >::Reset()
{
    m_markTime = ClockT::Now();
}


template< typename ClockT >
inline auto Stopwatch< ClockT >::Elapsed() const -> Duration
{
    return Duration( ClockT::Now() - m_markTime );
}


template< typename ClockT >
inline auto Stopwatch< ClockT >::Slice() -> Duration
{
    // This function is ALMOST equivalent to Elapsed() then Reset(),
    // but here we can use the same now in both functions.

    const TimePoint now = ClockT::Now();
    const Duration delta = now - m_markTime;
    m_markTime = now;
    return delta;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_STOPWATCH_H
