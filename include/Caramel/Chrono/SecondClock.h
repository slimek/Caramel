// Caramel C++ Library - Chrono Amenity - Second Clock Header

#ifndef __CARAMEL_CHRONO_SECOND_CLOCK_H
#define __CARAMEL_CHRONO_SECOND_CLOCK_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Chrono/SteadyClock.h>
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

    // void Reset();
    // Seconds Elasped() const;
    // Seconds Slice();
    // static SecondPoint Now();
    // static Seconds SinceEpoch();
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
    : Inherited( duration )
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
