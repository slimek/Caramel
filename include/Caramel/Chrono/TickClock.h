// Caramel C++ Library - Chrono Amenity - Tick Clock Header

#ifndef __CARAMEL_CHRONO_TICK_CLOCK_H
#define __CARAMEL_CHRONO_TICK_CLOCK_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Chrono/SteadyClock.h>
#include <Caramel/Numeric/NumberConvertible.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Tick Clock
//

class TickClock : public SteadyClock< Int64, boost::milli >
{
};


//
// Tick Duration
//

class TickDuration : public TickClock::Duration
                   , public NumberConvertible< TickDuration, Int64 >
{
public:

    TickDuration() {}
    
    TickDuration( const TickClock::Duration& tdur );
    TickDuration( TickClock::Duration&& tdur );

    explicit TickDuration( Int64 ticks );


    /// Converters ///

    Int64 ToNumber() const;

    Int32 ToInt32() const;
};


inline TickDuration Ticks( Int64 ticks )
{
    return TickDuration( ticks );
}


//
// Tick Point
//

class TickPoint : public TickClock::TimePoint
{
public:
    
    TickPoint( const TickClock::TimePoint& tpoint );
    TickPoint( TickClock::TimePoint&& tpoint );

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Tick Duration
//

inline TickDuration::TickDuration( const TickClock::Duration& tdur )
    : TickClock::Duration( tdur )
{
}


inline TickDuration::TickDuration( TickClock::Duration&& tdur )
    : TickClock::Duration( tdur )
{
}


inline TickDuration::TickDuration( Int64 ticks )
    : TickClock::Duration( ticks )
{
}


inline Int64 TickDuration::ToNumber() const
{
    return this->count();
}


inline Int32 TickDuration::ToInt32() const
{
    return static_cast< Int32 >( this->count() );
}


//
// Tick Point
//

inline TickPoint::TickPoint( const TickClock::TimePoint& tpoint )
    : TickClock::TimePoint( tpoint )
{
}


inline TickPoint::TickPoint( TickClock::TimePoint&& tpoint )
    : TickClock::TimePoint( tpoint )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_TICK_CLOCK_H
