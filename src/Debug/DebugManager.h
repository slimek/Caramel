// Caramel C++ Library - Debug Facility - Debug Manager Header

#ifndef __CARAMEL_DEBUG_DEBUG_MANAGER_H
#define __CARAMEL_DEBUG_DEBUG_MANAGER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Object/FacilityLongevity.h"
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Object/Singleton.h>
#include <atomic>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Debug Manager
//

class DebugManager : public Singleton< DebugManager, FACILITY_LONGEVITY_DEBUG >
{
public:

    /// Timing ///

    void UpdateTiming( Uint id, const Ticks& elapsed );

    void ReportTimingToTrace();


private:

    struct TimingEntry
    {
        std::atomic< Uint >     count;
        std::atomic< Int64 >    total;
    };

    static const Uint NUM_TIMINGS = 256;

    TimingEntry m_timings[ NUM_TIMINGS ];
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DEBUG_DEBUG_MANAGER_H
