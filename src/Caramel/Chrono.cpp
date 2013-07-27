// Caramel C++ Library - Chrono Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Chrono/ChronoManager.h>
#include <Caramel/Chrono/Detail/SteadyClockCore.h>


namespace Caramel
{

//
// Contents
//
//   ChronoManager
//   Detail::SteadyClockCore
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

} // namespace Caramel
