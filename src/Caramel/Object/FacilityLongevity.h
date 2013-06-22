// Caramel C++ Library - Object Facility - Facility Longevity Header

#ifndef __CARAMEL_OBJECT_FACILITY_LONGEVITY_H
#define __CARAMEL_OBJECT_FACILITY_LONGEVITY_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Facility Singleton Longevity Table
// - The higher level, the later destroyed.
//

enum FacilityLongevity
{
    FACILITY_LONGEVITY_LEVEL_0 = 0x80000000,

    // Level 0
    FACILITY_LONGEVITY_SPRINTF = FACILITY_LONGEVITY_LEVEL_0,
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_OBJECT_FACILITY_LONGEVITY_H
