// Caramel C++ Library Test - Random - Weighted Random Map Suite

#include "CaramelTestPch.h"

#include <Caramel/Random/WeightedRandomMap.h>


namespace Caramel
{

SUITE( WeightedRandomMapSuite )
{

TEST( WeightedRandomMapTrivialTest )
{
    WeightedRandomMap< Int, std::string > map;
    CHECK( true == map.IsEmpty() );
    
    map.Add( 1, "Alice" );
    CHECK( false == map.IsEmpty() );    
}


TEST( WeightedRandomMapTest )
{
    // Weight is Int
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

    // Weight is Float
    {
        WeightedRandomMap< Float, Int > map;

        map.Add( 0.01f, 0 );
        map.Add( 0.09f, 1 );
        map.Add( 0.9f, 2 );

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
}


} // SUITE WeightedRandomMapSuite

} // namespace Caramel
