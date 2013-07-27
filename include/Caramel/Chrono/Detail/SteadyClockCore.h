// Caramel C++ Library - Chrono Facility - Detail - Steady Clock Core Header

#ifndef __CARAMEL_CHRONO_DETAIL_STEADY_CLOCK_CORE_H
#define __CARAMEL_CHRONO_DETAIL_STEADY_CLOCK_CORE_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <chrono>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Steady Clock Core
// - A lightweight wrapper of std::steady_clock
//

class SteadyClockCore
{
public:

    typedef std::chrono::steady_clock ClockType;
    typedef ClockType::time_point TimePoint;


    //
    // Epoch
    // - In one run of program, it returns always the same time.
    //   You may treat it as "the start time of this run",
    //   but in fact is the time when Epoch() is first called.
    //
    static TimePoint Epoch();
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_CHRONO_DETAIL_STEADY_CLOCK_CORE_H
