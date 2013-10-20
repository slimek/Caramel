// Caramel C++ Library Test - Concurrent - Map Test

#include "CaramelTestPch.h"

#include <Caramel/Concurrent/Map.h>
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
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE ConcurrentMapSuite

} // namespace Caramel
