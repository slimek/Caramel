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
// Second Clock
//

class SecondClock : public SteadyClock< Double, boost::ratio< 1 > >
{
};


//
// Second Duration
//

class SecondDuration : public SecondClock::Duration
                     , public NumberConvertible< SecondDuration,  Double >
{
public:

    SecondDuration() {}

    SecondDuration( const SecondClock::Duration& sdur );
    SecondDuration( SecondClock::Duration&& sdur );

    explicit SecondDuration( Double seconds );


    /// Converters ///

    Double ToNumber() const;

    Float  ToFloat() const;
};


inline SecondDuration Seconds( Double seconds )
{
    return SecondDuration( seconds );
}


//
// Second Point
//

class SecondPoint : public SecondClock::TimePoint
{
public:
    
    SecondPoint( const SecondClock::TimePoint& spoint );
    SecondPoint( SecondClock::TimePoint&& spoint );
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

//
// Second Duration
//

inline SecondDuration::SecondDuration( const SecondClock::Duration& sdur )
    : SecondClock::Duration( sdur )
{
}


inline SecondDuration::SecondDuration( SecondClock::Duration&& sdur )
    : SecondClock::Duration( sdur )
{
}


inline SecondDuration::SecondDuration( Double seconds )
    : SecondClock::Duration( seconds )
{
}


inline Double SecondDuration::ToNumber() const
{
    return this->count();
}


inline Float SecondDuration::ToFloat() const
{
    return static_cast< Float >( this->count() );
}


//
// Second Point
//

inline SecondPoint::SecondPoint( const SecondClock::TimePoint& spoint )
    : SecondClock::TimePoint( spoint )
{
}


inline SecondPoint::SecondPoint( SecondClock::TimePoint&& spoint )
    : SecondClock::TimePoint( spoint )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_SECOND_CLOCK_H
