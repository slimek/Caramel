// Caramel C++ Library Test - Random - Weighted Random Map Test

#include "CaramelTestPch.h"

#include <Caramel/Random/WeightedRandomMap.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( WeightedRandomMapSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Test
//

TEST( WeightedRandomMapTest )
{
    WeightedRandomMap< Int, Int > map;

    map.Add( 1,  0 );
    map.Add( 9,  1 );
    map.Add( 90, 2 );

    Int counts[3] = { 0 };

    const Int BIAS = 1000;

    for ( Int i = 0; i < BIAS * 100; ++ i )
    {
        ++ counts[ map.Next() ];
    }

    CHECK_CLOSE(      BIAS, counts[0], BIAS / 10);
    CHECK_CLOSE(  9 * BIAS, counts[1], BIAS );
    CHECK_CLOSE( 90 * BIAS, counts[2], BIAS );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE WeightedRandomMapSuite

} // namespace Caramel
