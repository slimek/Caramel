// Caramel C++ Library Test - Concurrent - Map Suite

#include "CaramelTestPch.h"

#include "Utils/Matcher.h"
#include <Caramel/Concurrent/FlatMap.h>
#include <Caramel/Concurrent/HashMap.h>
#include <Caramel/Concurrent/Map.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( ConcurrentMapSuite )
{

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

    map.Erase( 2 );

    CHECK( false == map.Contains( 2 ));
    CHECK( 2 == map.Size() );

    map.Clear();

    CHECK( true == map.IsEmpty() );
    CHECK( 0 == map.Size() );
    CHECK( false == map.Contains( 1 ));

    typename MapType::UnderlyingType newMap;
    newMap.insert( std::make_pair( 6, std::string( "Aya" )));
    newMap.insert( std::make_pair( 7, std::string( "Nitori" )));

    map.Swap( newMap );

    CHECK( false == map.IsEmpty() );
    CHECK( 2 == map.Size() );
    CHECK( true == map.Contains( 7 ));
    CHECK( true == map.Find( 6, temp ));
    CHECK( "Aya" == temp );


    /// Combo Manipulators ///

    temp = "Utsuho";
    CHECK( false == map.FindOrInsert( 9, temp ));  // Not found, inserted

    temp = "Cirno";
    CHECK( true == map.FindOrInsert( 9, temp ));   // Found, not inserted
    CHECK( "Utsuho" == temp );


    /// Mutable Locked Map ///

    {
        typename MapType::LockedMap lockedMap( map );
        lockedMap.Clear();

        CHECK( true == map.IsEmpty() );

        lockedMap.Insert( 8, "Mystia" );
        lockedMap.Insert( 5, "Hina" );
    }

    CHECK( 2 == map.Size() );
    CHECK( true  == map.Contains( 8 ));
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
    auto vshot1 = map.GetValuesSnapshot();
    auto pshot1 = map.GetPairsSnapshot();

    CHECK( true == vshot1.IsEmpty() );
    CHECK( 0 == vshot1.Size() );
    CHECK( true == pshot1.IsEmpty() );
    CHECK( 0 == pshot1.Size() );

    map.Insert( 6, "Marisa" );
    map.Insert( 7, "Alice" );
    map.Insert( 8, "Patchou" );

    auto vshot2 = map.GetValuesSnapshot();
    auto pshot2 = map.GetPairsSnapshot();

    CHECK( false == vshot2.IsEmpty() );
    CHECK( 3 == vshot2.Size() );
    CHECK( Match< std::string >( vshot2, { "Marisa", "Alice", "Patchou" } ));
    CHECK( false == pshot2.IsEmpty() );
    CHECK( 3 == pshot2.Size() );
    CHECK( 8 == pshot2[2].first && "Patchou" == pshot2[2].second );

    map.Erase( 8 );

    auto vshot3 = map.GetValuesSnapshot();
    auto pshot3 = map.GetPairsSnapshot();

    CHECK( 2 == vshot3.Size() );
    CHECK( Match< std::string >( vshot3, { "Marisa", "Alice" } ));
    CHECK( 2 == pshot3.Size() );
    CHECK( 7 == pshot3[1].first && "Alice" == pshot3[1].second );

    map.Clear();

    auto vshot4 = map.GetValuesSnapshot();
    auto pshot4 = map.GetPairsSnapshot();

    CHECK( true == vshot4.IsEmpty() );
    CHECK( true == pshot4.IsEmpty() );


    typename MapType::UnderlyingType newMap;
    newMap.insert( std::make_pair( 1, std::string( "Hijiri" )));
    newMap.insert( std::make_pair( 2, std::string( "Kokoro" )));

    map.Swap( newMap );

    auto vshot5 = map.GetValuesSnapshot();

    CHECK( Match< std::string >( vshot5, { "Hijiri", "Kokoro" } ));
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


} // SUITE ConcurrentMapSuite

} // namespace Caramel
