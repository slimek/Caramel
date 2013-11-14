// Caramel C++ Library - Random Facility - Random Manager Header

#ifndef __CARAMEL_RANDOM_RANDOM_MANAGER_H
#define __CARAMEL_RANDOM_RANDOM_MANAGER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include "Object/FacilityLongevity.h"
#include "Random/RandomImpl.h"
#include <Caramel/Object/Singleton.h>
#include <Caramel/Thread/MutexLocks.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Random Manager
//


class RandomManager : public Singleton< RandomManager, FACILITY_LONGEVITY_RANDOM >
{
public:
    
    RandomManager();


    /// Global Ganerate Functions ///

    Uint GenRandomUint( Uint minValue, Uint maxValue );


private:

    RandomImpl m_random;

    std::mutex m_mutex;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_RANDOM_RANDOM_MANAGER_H
