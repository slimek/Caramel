// Caramel C++ Library - Chrono Facility - Durations Header

#ifndef __CARAMEL_CHRONO_DURATIONS_H
#define __CARAMEL_CHRONO_DURATIONS_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <chrono>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Tick Duration
// - Unit in milliseconds
//

class TickDuration : public std::chrono::duration< Uint64, std::milli >
{
    typedef std::chrono::duration< Uint64, std::milli > Inherited;

public:

    TickDuration();
    explicit TickDuration( Uint64 milliseconds );

};


inline TickDuration Ticks( Uint64 milliseconds )
{
    return TickDuration( milliseconds );
}


///////////////////////////////////////////////////////////////////////////////
//
// Second Duration
//

class SecondDuration
{
public:

    SecondDuration();
    explicit SecondDuration( Double seconds );


    /// Operators ///

    Bool operator<( const SecondDuration& rhs ) const { return m_value < rhs.m_value; }


private:

    Double m_value;
};


inline SecondDuration Seconds( Double seconds )
{
    return SecondDuration( seconds );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_DURATIONS_H
