// Caramel C++ Library Test - Concurrent - Set Suite

#include "CaramelTestPch.h"

#include "Utils/SharedArrayUtils.h"
#include <Caramel/Chrono/TimedBool.h>
#include <Caramel/Concurrent/FlatSet.h>
#include <Caramel/Concurrent/Set.h>
#include <Caramel/Random/UniformRandom.h>
#include <Caramel/Thread/ThisThread.h>
#include <Caramel/Thread/Thread.h>
#include <atomic>


namespace Caramel
{

SUITE( ConcurrentSetSuite )
{

template< typename SetType >
void TestBasicIntSet( SetType& set )
{
    CHECK( true == set.IsEmpty() );
    CHECK( 0    == set.Size() );

    CHECK( true == set.Insert( 42 ));

    CHECK( false == set.IsEmpty() );
    CHECK( 1     == set.Size() );
    CHECK( true  == set.Contains( 42 ));
    CHECK( false == set.Contains( 19 ));

    CHECK( false == set.Insert( 42 ));  // Already inserted

    CHECK( true == set.Insert( 24 ));
    CHECK( 2    == set.Size() );

    CHECK( 0    == set.Erase( 19 ));
    CHECK( 1    == set.Erase( 42 ));

    CHECK( false == set.Contains( 42 ));

    {
        typename SetType::ConstLockedSet lockedSet( set );
        auto ivalue = lockedSet.Begin();
        CHECK( 24 == *( ivalue ++ ));
        CHECK( lockedSet.End() == ivalue );
    }

    set.Clear();

    CHECK( true == set.IsEmpty() );

    std::vector< Int > ints{ 3, 5, 8 };

    CHECK( true == set.Insert( ints.begin(), ints.end() ));
    CHECK( true == set.Contains( 5 ));
    CHECK( 3    == set.Size() );

    set.Clear();

    ints = { 2, 2, 7 };

    CHECK( false == set.Insert( ints.begin(), ints.end() ));
    CHECK( true  == set.Contains( 2 ));
    CHECK( 2     == set.Size() );
}


//
// Concurrent Set Test
//

TEST( ConcurrentSetTest )
{
    Concurrent::Set< Int > iset;
    TestBasicIntSet( iset );
}


TEST( ConcurrentFlatSetTest )
{
    Concurrent::FlatSet< Int > iset;
    TestBasicIntSet( iset );
}


///////////////////////////////////////////////////////////////////////////////
//
// Basic Set with Snapshot Test
//

template< typename SetType >
void TestBasicSetWithSnapshot( SetType& set )
{
    typedef typename SetType::KeyType KeyType;

    auto shot1 = set.GetSnapshot();

    CHECK( true == shot1.IsEmpty() );
    CHECK( 0 == shot1.Size() );

    set.Insert( 6 );
    set.Insert( 7 );
    set.Insert( 8 );

    auto shot2 = set.GetSnapshot();

    CHECK( false == shot2.IsEmpty() );
    CHECK( 3 == shot2.Size() );
    CHECK(( shot2 == ConstSharedArray< KeyType >{ 6, 7, 8 } ));

    set.Erase( 7 );

    auto shot3 = set.GetSnapshot();

    CHECK( 2 == shot3.Size() );
    CHECK(( shot3 == ConstSharedArray< KeyType >{ 6, 8 } ));

    set.Clear();

    auto shot4 = set.GetSnapshot();

    CHECK( true == shot4.IsEmpty() );
}


//
// Concurrent Set with Snapshot Test
//

TEST( ConcurrentSetWithSnapshotTest )
{
    Concurrent::SetWithSnapshot< Int > iset;
    TestBasicSetWithSnapshot( iset );
}


TEST( ConcurrentFlatSetWithSnapshotTest )
{
    Concurrent::FlatSetWithSnapshot< Int > iset;
    TestBasicSetWithSnapshot( iset );
}


///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Set Snapshot Stress Test
//

TEST( ConcurrentSetSnapshotStressTest )
{
    const Int minInt = -256;
    const Int maxInt = 255;

    Concurrent::SetWithSnapshot< Int > iset;

    TimedBool< TickClock > timeup( 3000 );

    std::atomic< Int > inserts( 0 );
    std::atomic< Int > erases( 0 );
    std::atomic< Int > snapshots( 0 );

    Thread t1( "Inserter", [&]
    {
        while ( ! timeup )
        {
            iset.Insert( GenRandomInt( minInt, maxInt ));
            ++ inserts;
        }
    });
    
    Thread t2( "EraserOrInsert", [&]
    {
        while ( ! timeup )
        {
            if ( GenRandomBool( 0.8 ))
            {
                iset.Erase( GenRandomInt( minInt, maxInt ));
                ++ erases;
            }
            else
            {
                iset.Insert( GenRandomInt( minInt, maxInt ));
                ++ inserts;
            }
        }
    });

    Thread t3( "Snapshot", [&]
    {
        while ( ! timeup )
        {
            if ( GenRandomBool( 0.01 ))
            {
                auto snapshot = iset.GetSnapshot();
                ++ snapshots;
            }
            else
            {
                iset.Insert( GenRandomInt( minInt, maxInt ));
                ++ inserts;
            }
        }
    });

    t1.Join();
    t2.Join();
    t3.Join();

    CARAMEL_TRACE_INFO( "Inserts: {0} Erases: {1}, Snapshots: {2}",
                        inserts.load(), erases.load(), snapshots.load() );
}


} // SUITE ConcurrentSetSuite

} // namespace Caramel
