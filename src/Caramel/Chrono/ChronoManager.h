// Caramel C++ Library - Chrono Facility - Chrono Manager Header

#ifndef __CARAMEL_CHRONO_CHRONO_MANAGER_H
#define __CARAMEL_CHRONO_CHRONO_MANAGER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Object/Singleton.h>
#include <Caramel/Object/FacilityLongevity.h>
#include <chrono>


namespace Caramel
{

typedef std::chrono::steady_clock::time_point SteadyTimePoint;

///////////////////////////////////////////////////////////////////////////////
//
// Chrono Manager
//

class ChronoManager : public Singleton< ChronoManager, FACILITY_LONGEVITY_CHRONO >
{
public:

    ChronoManager();


    /// Overservers ///

    SteadyTimePoint GetSteadyEpoch() const { return m_steadyEpoch; }

    
private:

    SteadyTimePoint m_steadyEpoch;        
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CHRONO_CHRONO_MANAGER_H
