// Caramel C++ Library - Debug Facility - Scope Timing Header

#ifndef __CARAMEL_DEBUG_SCOPE_TIMING_H
#define __CARAMEL_DEBUG_SCOPE_TIMING_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Chrono/TickClock.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Scope Timing
// - A tools to measure how long a function call costs.
//   Base on TickClock.
//
//   The valid timing id is 0 - 255.
//

class ScopeTiming
{
public:
    explicit ScopeTiming( Uint8 timingId );
    ~ScopeTiming();

    void Stop();


    /// Facility Operatins ///

    static void ReportToTrace();


private:

    Uint8     m_timingId;
    TickPoint m_startTime;
    Bool      m_stopped;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DEBUG_SCOPE_TIMING_H
