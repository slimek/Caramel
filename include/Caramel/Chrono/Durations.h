// Caramel C++ Library - Chrono Facility - Durations Header

#ifndef __CARAMEL_CHRONO_DURATIONS_H
#define __CARAMEL_CHRONO_DURATIONS_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Tick Duration
// - Unit in milliseconds
//

class TickDuration
{
public:

    TickDuration();
    explicit TickDuration( Uint64 milliseconds );


    /// Operators ///

    Bool operator<( const TickDuration& rhs ) const { return m_value < rhs.m_value; }


private:

    Uint64 m_value;
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
