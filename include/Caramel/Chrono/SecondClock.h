// Caramel C++ Library - Chrono Amenity - Second Clock Header

#ifndef __CARAMEL_CHRONO_SECOND_CLOCK_H
#define __CARAMEL_CHRONO_SECOND_CLOCK_H

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

    explicit Seconds( Double ticks );


    /// Properties ///

    static Seconds Zero()     { return Seconds( Inherited::zero() ); }
    static Seconds MaxValue() { return Seconds( Inherited::max() ); }


    /// Convertions ///

    Double ToNumber() const { return this->count(); }

    Double ToDouble() const { return this->count(); }
    Float  ToFloat()  const { return static_cast< Float >( this->count() ); }
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

    static Seconds     MaxDuration()  { return Seconds::MaxValue(); }
    static SecondPoint MaxTimePoint() { return SecondPoint::MaxValue(); }
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


inline Seconds::Seconds( Double ticks )
    : Inherited( ticks )
{
}


//
// Tick Point
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
