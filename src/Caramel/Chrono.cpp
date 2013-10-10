// Caramel C++ Library - Chrono Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Chrono/ChronoManager.h>
#include <Caramel/Chrono/Detail/SteadyClockCore.h>
#include <Caramel/Chrono/Durations.h>


namespace Caramel
{

//
// Contents
//
//   ChronoManager
//   Detail::SteadyClockCore
//
// < Durations >
// 
//   TickDuration
//

///////////////////////////////////////////////////////////////////////////////
//
// Chrono Manager
//

ChronoManager::ChronoManager()
{
    m_steadyEpoch = std::chrono::steady_clock::now();
}


///////////////////////////////////////////////////////////////////////////////
//
// Steady Clock Core
//

namespace Detail
{

SteadyClockCore::TimePoint SteadyClockCore::Epoch()
{
    return ChronoManager::Instance()->GetSteadyEpoch();
}


} // namespace Detail

///////////////////////////////////////////////////////////////////////////////
//
// Tick Duration
//

TickDuration::TickDuration()
    : Inherited( 0 )
{
}


TickDuration::TickDuration( Uint64 ticks )
    : Inherited( ticks )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
