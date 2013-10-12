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

    template< typename Rep, typename Period >
    TickDuration( const boost::chrono::duration< Rep, Period >& duration );

    explicit TickDuration( Int64 ticks );


    /// Properties ///

    static TickDuration Zero()     { return TickDuration( TickClock::Duration::zero() ); }
    static TickDuration MaxValue() { return TickDuration( TickClock::Duration::max() ); }


    /// Convertions ///

    Int64 ToNumber() const { return this->count(); }

    Int64 ToInt64()  const { return this->count(); }
    Int32 ToInt32()  const { return static_cast< Int32 >( this->count() ); }
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


    /// Properties ///

    static TickPoint MaxValue() { return TickClock::TimePoint::max(); }
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


template< typename Rep, typename Period >
inline TickDuration::TickDuration( const boost::chrono::duration< Rep, Period >& duration )
    : TickClock::Duration( boost::chrono::duration_cast< TickClock::Duration >( duration ))
{
}


inline TickDuration::TickDuration( Int64 ticks )
    : TickClock::Duration( ticks )
{
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
