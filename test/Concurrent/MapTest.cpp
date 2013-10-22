// Caramel C++ Library Test - Concurrent - Map Test

#include "CaramelTestPch.h"

#include <Caramel/Concurrent/Map.h>
#include <Caramel/Concurrent/HashMap.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( ConcurrentMapSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Map Test
//

TEST( ConcurrentMapTest )
{
    typedef Concurrent::Map< Int, std::string > MapType;
    MapType map;

    CHECK( true == map.IsEmpty() );
    CHECK( 0 == map.Size() );

    map.Insert( 1, "Reimu" );
    map.Insert( 2, "Marisa" );
    map.Insert( 3, "Alice" );

    CHECK( false == map.Insert( 3, "Pachouli" ));

    CHECK( true == map.Contains( 1 ));
    CHECK( false == map.Contains( 4 ));

    std::string temp;
    CHECK( true == map.Find( 1, temp ));
    CHECK( "Reimu" == temp );

    CHECK( false == map.Find( 4, temp ));
}


///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Hash Map Test
//

TEST( ConcurrentHashMapTest )
{
    typedef Concurrent::HashMap< Int, std::string > MapType;
    MapType map;

    CHECK( true == map.IsEmpty() );
    CHECK( 0 == map.Size() );

    map.Insert( 1, "Reimu" );
    map.Insert( 2, "Marisa" );
    map.Insert( 3, "Alice" );

    CHECK( false == map.Insert( 3, "Pachouli" ));

    CHECK( true == map.Contains( 1 ));
    CHECK( false == map.Contains( 4 ));

    std::string temp;
    CHECK( true == map.Find( 1, temp ));
    CHECK( "Reimu" == temp );

    CHECK( false == map.Find( 4, temp ));
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE ConcurrentMapSuite

} // namespace Caramel
