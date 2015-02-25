// Caramel C++ Library - Debug Facility - Implementation

#include "CaramelPch.h"

#include "Debug/DebugManager.h"
#include <Caramel/Debug/ScopeTiming.h>


namespace Caramel
{

//
// Contents
//
//   DebugManager
//   ScopeTiming
//

///////////////////////////////////////////////////////////////////////////////
//
// Debug Manager
//

void DebugManager::UpdateTiming( Uint id, const Ticks& elapsed )
{
    CARAMEL_ASSERT( NUM_TIMINGS > id );

    ++ m_timings[id].count;
    m_timings[id].total.fetch_add( elapsed.ToInt64() );
}


void DebugManager::ReportTimingToTrace()
{
    TraceDebug( "<Timing Report>" );

    for ( Uint i = 0; i < NUM_TIMINGS; ++ i )
    {
        const Uint count = m_timings[i].count;

        if ( 0 == count ) { continue; }

        const Uint64 total = m_timings[i].total;

        TraceDebug( "[{0}] : {1} ms / {2}", i, total, count );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Scope Timing
//

ScopeTiming::ScopeTiming( Uint8 timingId )
    : m_timingId( timingId )
    , m_startTime( TickClock::Now() )
    , m_stopped( false )
{
}


ScopeTiming::~ScopeTiming()
{
    this->Stop();
}


void ScopeTiming::Stop()
{
    if ( m_stopped ) { return; }

    m_stopped = true;

    const Ticks elapsed = TickClock::Now() - m_startTime;

    DebugManager::Instance()->UpdateTiming( m_timingId, elapsed );
}


void ScopeTiming::ReportToTrace()
{
    DebugManager::Instance()->ReportTimingToTrace();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
