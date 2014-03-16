// Caramel C++ Library - Chrono Amenity - Tick Clock Header

#ifndef __CARAMEL_CHRONO_TICK_CLOCK_H
#define __CARAMEL_CHRONO_TICK_CLOCK_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Chrono/SteadyClock.h>
#include <Caramel/Chrono/Stopwatch.h>
#include <Caramel/Numeric/NumberConvertible.h>
#include <chrono>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Tick Clock Classes
//

//
// Ticks - Tick Duration
//

class Ticks : public boost::chrono::duration< Int64, boost::milli >
            , public NumberConvertible< Ticks, Int64 >
{
    typedef boost::chrono::duration< Int64, boost::milli > Inherited;

public:

    Ticks() {}
    
    Ticks( const Inherited& duration );
    Ticks( Inherited&& duration );

    template< typename Rep, typename Period >
    Ticks( const boost::chrono::duration< Rep, Period >& duration );

    explicit Ticks( Int64 ticks );


    /// Properties ///

    static Ticks Zero()     { return Ticks( Inherited::zero() ); }
    static Ticks MaxValue() { return Ticks( Inherited::max() ); }


    /// Convertions ///

    Int64 ToNumber() const { return this->count(); }

    Int64 ToInt64()  const { return this->count(); }
    Int32 ToInt32()  const { return static_cast< Int32 >( this->count() ); }

    typedef std::chrono::duration< Int64, std::milli > StdDuration;
    StdDuration ToStdDuration() const { return StdDuration( this->count() ); }
};


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

class TickClock : public SteadyClock< Ticks, TickPoint >
{
public:

    /// Inherited Functions: ///

    // static TickPoint Now();
    // static Ticks SinceEpoch();
};


//
// Tick Stopwatch
//

class TickWatch : public Stopwatch< TickClock >
{
public:

    /// Inherited Functions: ///

    // void Reset();
    // Ticks Elasped() const;
    // Ticks Slice();
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Tick Duration
//

inline Ticks::Ticks( const Inherited& duration )
    : Inherited( duration )
{
}


inline Ticks::Ticks( Inherited&& duration )
    : Inherited( duration )
{
}


template< typename Rep, typename Period >
inline Ticks::Ticks( const boost::chrono::duration< Rep, Period >& duration )
    : Inherited( boost::chrono::duration_cast< Inherited >( duration ))
{
}


inline Ticks::Ticks( Int64 ticks )
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
