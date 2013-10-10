// Caramel C++ Library - Chrono Facility - Tick Clock Header

#ifndef __CARAMEL_CHRONO_TICK_CLOCK_H
#define __CARAMEL_CHRONO_TICK_CLOCK_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Chrono/ChronoFwd.h>
#include <Caramel/Chrono/SteadyClock.h>
#include <Caramel/Numeric/NumberConvertible.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Tick Clock
//

class TickClock : public SteadyClock< Int64, std::milli >
{
public:

    static TickPoint Now();
};


///////////////////////////////////////////////////////////////////////////////
//
// Tick Duration
//

class TickDuration : public TickClock::DurationType
                   , public NumberConvertible< TickDuration, Int64 >
{
    typedef TickClock::DurationType Inherited;

public:

    TickDuration();
    
    explicit TickDuration( Int64 ticks );

    /// Converters ///

    Int64 ToNumber() const;
};


inline TickDuration Ticks( Int64 ticks )
{
    return TickDuration( ticks );
}


///////////////////////////////////////////////////////////////////////////////
//
// Tick Point
//

class TickPoint : public std::chrono::time_point< TickClock, TickDuration >
                , public NumberConvertible< TickPoint, Int64 >
{
    typedef std::chrono::time_point< TickClock, TickDuration > Inherited;

public:
    
    /// Converters ///

    Int64 ToNumber() const;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_TICK_CLOCK_H
