// Caramel C++ Library - Object Facility - Facility Longevity Header

#ifndef __CARAMEL_OBJECT_FACILITY_LONGEVITY_H
#define __CARAMEL_OBJECT_FACILITY_LONGEVITY_H
#pragma once

#include <Caramel/Caramel.h>


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
    FACILITY_LONGEVITY_LEVEL_1 = 0x80000001,
    FACILITY_LONGEVITY_LEVEL_2 = 0x80000002,
    FACILITY_LONGEVITY_LEVEL_3 = 0x80000003,
    FACILITY_LONGEVITY_LEVEL_4 = 0x80000004,

    // Level 0
    FACILITY_LONGEVITY_DATE_TIME        = FACILITY_LONGEVITY_LEVEL_0,
    FACILITY_LONGEVITY_DEBUG            = FACILITY_LONGEVITY_LEVEL_0,
    FACILITY_LONGEVITY_RANDOM           = FACILITY_LONGEVITY_LEVEL_0,

    // Level 1
    FACILITY_LONGEVITY_PROGRAM_OPTIONS  = FACILITY_LONGEVITY_LEVEL_1,

    // Level 2
    FACILITY_LONGEVITY_TRACE            = FACILITY_LONGEVITY_LEVEL_2,
    
    // Level 3
    FACILITY_LONGEVITY_SPRINTF          = FACILITY_LONGEVITY_LEVEL_3,

    // Level 4
    FACILITY_LONGEVITY_ERROR            = FACILITY_LONGEVITY_LEVEL_4,
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_OBJECT_FACILITY_LONGEVITY_H
