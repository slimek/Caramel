// Caramel C++ Library - Chrono Amenity - Tick Clock Header

#ifndef __CARAMEL_CHRONO_TICK_CLOCK_H
#define __CARAMEL_CHRONO_TICK_CLOCK_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Chrono/Stopwatch.h>
#include <Caramel/Chrono/TimedBool.h>
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
    typedef StdDuration::rep Rep;

    
    /// Constructors ///

    Ticks();  // default value = 0

    Ticks( const StdDuration& duration );

    template< typename Rep2, typename Period2 >
    Ticks( const std::chrono::duration< Rep2, Period2 >& duration );

    explicit Ticks( Int64 ticks );


    /// Constants ///

    static Ticks Zero()     { return Ticks( StdDuration::zero() ); }
    static Ticks MaxValue() { return Ticks( StdDuration::max() ); }


    /// Convertions ///

    // Implements NumberConvertible
    Int64 ToNumber() const { return this->count(); }

    Int64 ToInt64() const { return this->count(); }
    Int32 ToInt32() const { return static_cast< Int32 >( this->count() ); }


    /// Operations ///

    // Results in quotient and remainder
    struct DivideResult;
    DivideResult DivideBy( const Ticks& divisor ) const;


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
// Tick Clock derivative classes
//

typedef Stopwatch< TickClock > TickWatch;
typedef TimedBool< TickClock > TicksBool;


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


template< typename Rep2, typename Period2 >
inline Ticks::Ticks( const std::chrono::duration< Rep2, Period2 >& duration )
    : StdDuration( std::chrono::duration_cast< StdDuration >( duration ))
{}


inline Ticks::Ticks( Int64 ticks )
    : StdDuration( ticks )
{}


//
// Ticks Operations
//

struct Ticks::DivideResult
{
    DivideResult() : quotient( 0 ) {}

    Int64 quotient;
    Ticks remainder;
};


inline Ticks::DivideResult Ticks::DivideBy( const Ticks& divisor ) const
{
    DivideResult result;

    result.quotient = static_cast< const StdDuration& >( *this )
                    / static_cast< const StdDuration& >( divisor );

    result.remainder = static_cast< const StdDuration& >( *this )
                     % static_cast< const StdDuration& >( divisor );

    // TODO: In Visual C++ 2015, the below code doesn't compile. I don't know why...
    //   result.quotient  = *this / divisor;
    //   result.remainder = *this % divisor;

    return result;
}


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
