// Caramel C++ Library - Debug Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Debug/DebugManager.h>
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

void DebugManager::UpdateTiming( Uint id, const TickDuration& elapsed )
{
    CARAMEL_ASSERT( NUM_TIMINGS > id );

    ++ m_timings[id].count;
    m_timings[id].total.fetch_add( elapsed.ToInt64() );
}


///////////////////////////////////////////////////////////////////////////////
//
// Scope Timing
//

ScopeTiming::ScopeTiming( Uint8 timingId )
    : m_timingId( 0 )
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

    const TickDuration elapsed = TickClock::Now() - m_startTime;

    DebugManager::Instance()->UpdateTiming( m_timingId, elapsed );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
