// Caramel C++ Library Test - Concurrent - Map Test

#include "CaramelTestPch.h"

#include "Utils/SharedArrayUtils.h"
#include <Caramel/Concurrent/FlatMap.h>
#include <Caramel/Concurrent/HashMap.h>
#include <Caramel/Concurrent/Map.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( ConcurrentMapSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Basic Map Test
//

template< typename MapType >
void TestBasicMap( MapType& map )
{
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
// Concurrent Map Test
//

TEST( ConcurrentMapTest )
{
    typedef Concurrent::Map< Int, std::string > MapType;
    MapType map;

    TestBasicMap( map );
}


///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Hash Map Test
//

TEST( ConcurrentHashMapTest )
{
    typedef Concurrent::HashMap< Int, std::string > MapType;
    MapType map;

    TestBasicMap( map );
}


///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Flat Map Test
//

TEST( ConcurrentFlatMapTest )
{
    typedef Concurrent::FlatMap< Int, std::string > MapType;
    MapType map;

    TestBasicMap( map );
}


///////////////////////////////////////////////////////////////////////////////
//
// Basic Map with Snapshot Test
//

template< typename MapType >
void TestBasicMapWithSnapshot( MapType& map )
{
    auto shot1 = map.GetValuesSnapshot();

    CHECK( true == shot1.IsEmpty() );
    CHECK( 0 == shot1.Size() );

    map.Insert( 6, "Marisa" );
    map.Insert( 7, "Alice" );
    map.Insert( 8, "Patchou" );

    auto shot2 = map.GetValuesSnapshot();

    CHECK( false == shot2.IsEmpty() );
    CHECK( 3 == shot2.Size() );

    CHECK( shot2 == MakeConstSharedArray< std::string >( "Marisa", "Alice", "Patchou" ));
}


TEST( ConcurrentMapWithSnapshotTest )
{
    Concurrent::MapWithSnapshot< Int, std::string > imap;
    TestBasicMapWithSnapshot( imap );
}


TEST( ConcurrentHashMapWithSnapshotTest )
{
    Concurrent::HashMapWithSnapshot< Int, std::string > imap;
    TestBasicMapWithSnapshot( imap );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE ConcurrentMapSuite

} // namespace Caramel
