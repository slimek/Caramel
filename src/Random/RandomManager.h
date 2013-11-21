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

    Int32  GenRandomInt32 ( Int32  minValue, Int32  maxValue );
    Uint32 GenRandomUint32( Uint32 minValue, Uint32 maxValue );

    Float GenRandomFloat( Float lowerBound, Float upperBound );


private:

    RandomImpl m_random;

    std::mutex m_mutex;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_RANDOM_RANDOM_MANAGER_H
