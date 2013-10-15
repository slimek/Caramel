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
// Second Duration
//

class SecondDuration : public boost::chrono::duration< Double, boost::ratio< 1 > >
                     , public NumberConvertible< SecondDuration, Double >
{
    typedef boost::chrono::duration< Double, boost::ratio< 1 > > Inherited;

public:

    SecondDuration() {}
    
    SecondDuration( const Inherited& duration );
    SecondDuration( Inherited&& duration );

    template< typename Rep, typename Period >
    SecondDuration( const boost::chrono::duration< Rep, Period >& duration );

    explicit SecondDuration( Double ticks );


    /// Properties ///

    static SecondDuration Zero()     { return SecondDuration( Inherited::zero() ); }
    static SecondDuration MaxValue() { return SecondDuration( Inherited::max() ); }


    /// Convertions ///

    Double ToNumber() const { return this->count(); }

    Double ToDouble() const { return this->count(); }
    Float  ToFloat()  const { return static_cast< Float >( this->count() ); }
};


inline SecondDuration Seconds( Double ticks )
{
    return SecondDuration( ticks );
}


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

class SecondClock : public SteadyClock< SecondDuration, SecondPoint >
{
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Second Duration
//

inline SecondDuration::SecondDuration( const Inherited& duration )
    : Inherited( duration )
{
}


inline SecondDuration::SecondDuration( Inherited&& duration )
    : Inherited( duration )
{
}


template< typename Rep, typename Period >
inline SecondDuration::SecondDuration( const boost::chrono::duration< Rep, Period >& duration )
    : Inherited( boost::chrono::duration_cast< Inherited >( duration ))
{
}


inline SecondDuration::SecondDuration( Double ticks )
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
