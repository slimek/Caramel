// Caramel C++ Library - Chrono Facility - Time Points Header

#ifndef __CARAMEL_CHRONO_TIME_POINTS_H
#define __CARAMEL_CHRONO_TIME_POINTS_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Chrono/Durations.h>
#include <Caramel/Chrono/SteadyClock.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Tick Time Point
//

class TickPoint : public std::chrono::time_point< TickClock, TickDuration >
{
public:

    TickPoint();
    TickPoint( Uint64 ticks );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_TIME_POINTS_H
