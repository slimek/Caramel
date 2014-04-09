// Caramel C++ Library - Chrono Amenity - Second Clock Header

#ifndef __CARAMEL_CHRONO_SECOND_CLOCK_H
#define __CARAMEL_CHRONO_SECOND_CLOCK_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Chrono/SteadyClock.h>
#include <Caramel/Chrono/Stopwatch.h>
#include <Caramel/Math/Floating.h>
#include <Caramel/Numeric/NumberConvertible.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Second Clock Classes
//

//
// Seconds - Second Duration
//

class Seconds : public boost::chrono::duration< Double, boost::ratio< 1 > >
              , public NumberConvertible< Seconds, Double >
{
    typedef boost::chrono::duration< Double, boost::ratio< 1 > > Inherited;

public:

    Seconds() {}
    
    Seconds( const Inherited& duration );
    Seconds( Inherited&& duration );

    template< typename Rep, typename Period >
    Seconds( const boost::chrono::duration< Rep, Period >& duration );

    explicit Seconds( Double seconds );


    /// Properties ///

    static Seconds Zero()     { return Seconds( Inherited::zero() ); }
    static Seconds MaxValue() { return Seconds( Inherited::max() ); }


    /// Convertions ///

    Double ToNumber() const { return this->count(); }

    Double ToDouble() const { return this->count(); }
    Float  ToFloat()  const { return static_cast< Float >( this->count() ); }


    /// Operators ///

    // Removing the fraction part, results in an integral value.
    void Trunc();
    static Seconds TruncFrom( const Seconds& s );

    // Results in quotient and remainder.
    struct DivideResult;
    DivideResult DivideBy( const Seconds& divisor ) const;
};


//
// Second Point
//

class SecondPoint
    : public boost::chrono::time_point<
        boost::chrono::steady_clock, boost::chrono::duration< Double, boost::ratio< 1 > >
      >
{
    typedef boost::chrono::time_point<
        boost::chrono::steady_clock, boost::chrono::duration< Double, boost::ratio< 1 > >
    > Inherited;

public:
    
    typedef boost::chrono::duration< Double, boost::ratio< 1 > > Duration;

    SecondPoint() {}

    SecondPoint( const Inherited& tpoint );
    SecondPoint( Inherited&& tpoint );


    /// Properties ///

    static SecondPoint MaxValue() { return Inherited::max(); }
};


//
// Second Clock
//

class SecondClock : public SteadyClock< Seconds, SecondPoint >
{
public:

    /// Inherited Functions: ///

    // static SecondPoint Now();
    // static Seconds SinceEpoch();
};


//
// Second Stopwatch
//

class SecondWatch : public Stopwatch< SecondClock >
{
public:

    /// Inherited Functions: ///

    // void Reset();
    // Seconds Elasped() const;
    // Seconds Slice();
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Second Duration
//

inline Seconds::Seconds( const Inherited& duration )
    : Inherited( duration )
{
}


inline Seconds::Seconds( Inherited&& duration )
    : Inherited( std::move( duration ))
{
}


template< typename Rep, typename Period >
inline Seconds::Seconds( const boost::chrono::duration< Rep, Period >& duration )
    : Inherited( boost::chrono::duration_cast< Inherited >( duration ))
{
}


inline Seconds::Seconds( Double seconds )
    : Inherited( seconds )
{
}


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
    const Double q = Math::Trunc( this->count() / divisor.count() );

    DivideResult result;

    result.quotient  = static_cast< Int64 >( q );
    result.remainder = Seconds( this->count() - ( divisor.count() * q ));
    
    return result;
}


//
// Second Point
//

inline SecondPoint::SecondPoint( const Inherited& tpoint )
    : Inherited( tpoint )
{
}


inline SecondPoint::SecondPoint( Inherited&& tpoint )
    : Inherited( tpoint )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_SECOND_CLOCK_H
