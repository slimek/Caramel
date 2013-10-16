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
// Tick Clock Classes
//

//
// Tick Duration
//

class TickDuration : public boost::chrono::duration< Int64, boost::milli >
                   , public NumberConvertible< TickDuration, Int64 >
{
    typedef boost::chrono::duration< Int64, boost::milli > Inherited;

public:

    TickDuration() {}
    
    TickDuration( const Inherited& duration );
    TickDuration( Inherited&& duration );

    template< typename Rep, typename Period >
    TickDuration( const boost::chrono::duration< Rep, Period >& duration );

    explicit TickDuration( Int64 ticks );


    /// Properties ///

    static TickDuration Zero()     { return TickDuration( Inherited::zero() ); }
    static TickDuration MaxValue() { return TickDuration( Inherited::max() ); }


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

class TickPoint
    : public boost::chrono::time_point<
        boost::chrono::steady_clock, boost::chrono::duration< Int64, boost::milli >
      >
{
    typedef boost::chrono::time_point<
        boost::chrono::steady_clock, boost::chrono::duration< Int64, boost::milli >
    > Inherited;

public:
    
    typedef boost::chrono::duration< Int64, boost::milli > Duration;

    TickPoint() {}

    TickPoint( const Inherited& tpoint );
    TickPoint( Inherited&& tpoint );


    /// Properties ///

    static TickPoint MaxValue() { return Inherited::max(); }
};


//
// Tick Clock
//

class TickClock : public SteadyClock< TickDuration, TickPoint >
{
public:

    static TickDuration MaxDuration()  { return TickDuration::MaxValue(); }
    static TickPoint    MaxTimePoint() { return TickPoint::MaxValue(); }
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Tick Duration
//

inline TickDuration::TickDuration( const Inherited& duration )
    : Inherited( duration )
{
}


inline TickDuration::TickDuration( Inherited&& duration )
    : Inherited( duration )
{
}


template< typename Rep, typename Period >
inline TickDuration::TickDuration( const boost::chrono::duration< Rep, Period >& duration )
    : Inherited( boost::chrono::duration_cast< Inherited >( duration ))
{
}


inline TickDuration::TickDuration( Int64 ticks )
    : Inherited( ticks )
{
}


//
// Tick Point
//

inline TickPoint::TickPoint( const Inherited& tpoint )
    : Inherited( tpoint )
{
}


inline TickPoint::TickPoint( Inherited&& tpoint )
    : Inherited( tpoint )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_TICK_CLOCK_H
