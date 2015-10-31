// Caramel C++ Library - Chrono Amenity - Tick Clock Header

#ifndef __CARAMEL_CHRONO_TICK_CLOCK_H
#define __CARAMEL_CHRONO_TICK_CLOCK_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Chrono/Stopwatch.h>
#include <Caramel/Numeric/NumberConvertible.h>
#include <chrono>


namespace Caramel
{

//
// Tick Clock classes
// - This header provides five classes by tick (millisecond) time uint:
//      Ticks
//      TickPoint
//      TickClock
//      TickWatch
//      TicksBool
//

///////////////////////////////////////////////////////////////////////////////
//
// Ticks (Tick Duration)
//

class Ticks : public std::chrono::duration< Int64, std::milli >
            , public NumberConvertible< Ticks, Int64 >
{
public:

    typedef std::chrono::duration< Int64, std::milli > StdDuration;

    
    /// Constructors ///

    Ticks();  // default value = 0

    Ticks( const StdDuration& duration );

    template< typename Rep, typename Period >
    Ticks( const std::chrono::duration< Rep, Period >& duration );

    explicit Ticks( Int64 ticks );


    /// Constants ///

    static Ticks Zero()     { return Ticks( StdDuration::zero() ); }
    static Ticks MaxValue() { return Ticks( StdDuration::max() ); }


    /// Convertions ///

    // Implements NumberConvertible
    Int64 ToNumber() const { return this->count(); }

    Int64 ToInt64() const { return this->count(); }
    Int32 ToInt32() const { return static_cast< Int32 >( this->count() ); }

private:

    friend class TickPoint;
    friend class TickClock;
};


///////////////////////////////////////////////////////////////////////////////
//
// Tick Point
//

class TickPoint
    : public std::chrono::time_point< std::chrono::steady_clock, Ticks::StdDuration >
{
public:

    typedef std::chrono::time_point<
        std::chrono::steady_clock, Ticks::StdDuration > StdTimePoint;
    

    /// Constructors ///

    TickPoint() {}

    TickPoint( const StdTimePoint& tpoint );


    /// Constants ///

    static TickPoint MaxValue() { return TickPoint( StdTimePoint::max() ); }
};


///////////////////////////////////////////////////////////////////////////////
//
// Tick Clock
//

class TickClock
{
public:
    
    typedef Ticks Duration;
    typedef TickPoint TimePoint;

    static TickPoint Now();
};


///////////////////////////////////////////////////////////////////////////////
//
// Tick Stopwatch
//

typedef Stopwatch< TickClock > TickWatch;


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Ticks - Constructors
//

inline Ticks::Ticks()
    : StdDuration( 0 )
{}


inline Ticks::Ticks( const StdDuration& duration )
    : StdDuration( duration )
{}


template< typename Rep, typename Period >
inline Ticks::Ticks( const std::chrono::duration< Rep, Period >& duration )
    : StdDuration( std::chrono::duration_cast< StdDuration >( duration ))
{}


inline Ticks::Ticks( Int64 ticks )
    : StdDuration( ticks )
{}


//
// Tick Point
//

inline TickPoint::TickPoint( const StdTimePoint& tpoint )
    : StdTimePoint( tpoint )
{}


//
// Tick Clock
//

inline TickPoint TickClock::Now()
{
    return TickPoint(
        std::chrono::time_point_cast< Ticks::StdDuration >( std::chrono::steady_clock::now() ));
}


} // namespace Caramel


///////////////////////////////////////////////////////////////////////////////
//
// Traits helper for division of Ticks.
// - Without this trait, Visual C++ 2015 will fail to compile.
//

namespace std
{

template<>
struct common_type< Caramel::Int64, Caramel::Ticks >
{
    typedef Caramel::Int64 type;
};

} // namespace std


#endif // __CARAMEL_CHRONO_TICK_CLOCK_H
