// Caramel C++ Library - Chrono Amenity - Second Clock Header

#ifndef __CARAMEL_CHRONO_SECOND_CLOCK_H
#define __CARAMEL_CHRONO_SECOND_CLOCK_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Chrono/Stopwatch.h>
#include <Caramel/Chrono/TimedBool.h>
#include <Caramel/Math/Floating.h>
#include <Caramel/Numeric/NumberConvertible.h>
#include <chrono>


namespace Caramel
{

//
// Second Clock classes
// - This header provides five classes by second time unit:
//     Seconds
//     SecondPoint
//     SecondClock
//     SecondWatch
//     SecondsBool
//

///////////////////////////////////////////////////////////////////////////////
//
// Seconds (Second Duration)
//

class Seconds : public std::chrono::duration< Double, std::ratio< 1 >>
              , public NumberConvertible< Seconds, Double >
{
public:

    typedef std::chrono::duration< Double, std::ratio< 1 >> StdDuration;


    /// Constructors ///

    Seconds();  // default value = 0;

    Seconds( const StdDuration& duration );

    template< typename Rep, typename Period >
    Seconds( const std::chrono::duration< Rep, Period >& duration );

    explicit Seconds( Double seconds );


    /// Constants ///

    static Seconds Zero()     { return Seconds( StdDuration::zero() ); }
    static Seconds MaxValue() { return Seconds( StdDuration::max() ); }


    /// Convertions ///

    // Implements NumberConvertible
    Double ToNumber() const { return this->count(); }

    Double ToDouble() const { return this->count(); } 
    Float  ToFloat()  const { return static_cast< Float >( this->count() ); }


    /// Operators ///

    // NOTES: In Visual C++ 2015, you must override these division operators,
    //        or it doesn't compile.

    friend Double  operator/( const Seconds& duration, const Seconds& period );
    friend Seconds operator%( const Seconds& duration, const Seconds& period );


    /// Operations ///

    // Removing the fraction part, results in an integral value.
    void Trunc();
    static Seconds TruncFrom( const Seconds& s );

    // Results in quotient and remainder.
    struct DivideResult;
    DivideResult DivideBy( const Seconds& divisor ) const;


private:

    friend class SecondPoint;
    friend class SecondClock;
};


///////////////////////////////////////////////////////////////////////////////
//
// Second Point
//

class SecondPoint
    : public std::chrono::time_point< std::chrono::steady_clock, Seconds::StdDuration >
{
    typedef std::chrono::time_point<
        std::chrono::steady_clock, std::chrono::duration< Double, std::ratio< 1 >>
    > Inherited;

public:

    typedef std::chrono::time_point<
        std::chrono::steady_clock, Seconds::StdDuration > StdTimePoint;

    /// Constructors ///

    SecondPoint() {}

    SecondPoint( const StdTimePoint& tpoint );


    /// Constants ///

    static SecondPoint MaxValue() { return SecondPoint( StdTimePoint::max() ); }
};


///////////////////////////////////////////////////////////////////////////////
//
// Second Clock
//

class SecondClock
{
public:

    typedef Seconds Duration;
    typedef SecondPoint TimePoint;

    static SecondPoint Now();
};


///////////////////////////////////////////////////////////////////////////////
//
// Second Clock derivative classes
//

typedef Stopwatch< SecondClock > SecondWatch;
typedef TimedBool< SecondClock > SecondsBool;


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Seconds - Constructurs
//

inline Seconds::Seconds()
    : StdDuration( 0 )
{}


inline Seconds::Seconds( const StdDuration& duration )
    : StdDuration( duration )
{}


template< typename Rep, typename Period >
inline Seconds::Seconds( const std::chrono::duration< Rep, Period >& duration )
    : StdDuration( std::chrono::duration_cast< StdDuration >( duration ))
{}


inline Seconds::Seconds( Double seconds )
    : StdDuration( seconds )
{}


//
// Seconds - Operators
//

inline Double operator/( const Seconds& duration, const Seconds& period )
{
    return static_cast< const Seconds::StdDuration& >( duration )
         / static_cast< const Seconds::StdDuration& >( period );
}


inline Seconds operator%( const Seconds& duration, const Seconds& period )
{
    return Seconds( std::fmod( duration.count(), period.count() ));

    // NOTES: In Visual C++ 2015, the below code doesn't compile.
    //        Maybe it doesn't support remainder of floating?

    //return Seconds( static_cast< const Seconds::StdDuration& >( duration )
    //              % static_cast< const Seconds::StdDuration& >( period ));
}


//
// Seconds - Operations
//

inline void Seconds::Trunc()
{
    *this = TruncFrom( *this );
}


inline Seconds Seconds::TruncFrom( const Seconds& s )
{
    return Seconds( Math::Trunc( s.ToDouble() ));
}


struct Seconds::DivideResult
{
    DivideResult() : quotient( 0 ) {}

    Int64   quotient;
    Seconds remainder;
};


inline Seconds::DivideResult Seconds::DivideBy( const Seconds& divisor ) const
{
    DivideResult result;

    result.quotient  = static_cast< Int64 >( Caramel::operator/( *this, divisor ));
    result.remainder = Caramel::operator%( *this, divisor );

    // TODO: In Visual C++ 2015, the below code doesn't compile. I don't know why...
    //   result.quotient  = *this / divisor;
    //   result.remainder = *this % divisor;

    return result;
}


//
// Second Point
//

inline SecondPoint::SecondPoint( const StdTimePoint& tpoint )
    : StdTimePoint( tpoint )
{}


//
// Second Clock
//

inline SecondPoint SecondClock::Now()
{
    return SecondPoint(
        std::chrono::time_point_cast< Seconds::StdDuration >( std::chrono::steady_clock::now() ));
}


} // namespace Caramel


///////////////////////////////////////////////////////////////////////////////
//
// Helper trait for division of Seconds.
// - Without this trait, Visual C++ 2015 doesn't compile.
//

namespace std
{

template<>
struct common_type< Caramel::Double, Caramel::Seconds >
{
    typedef Caramel::Double type;
};

} // namespace std


#endif // __CARAMEL_CHRONO_SECOND_CLOCK_H
