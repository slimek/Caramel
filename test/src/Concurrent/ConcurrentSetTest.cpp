// Caramel C++ Library Test - Concurrent - Set Test

#include "CaramelTestPch.h"

#include <Caramel/Concurrent/Set.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( ConcurrentSetSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Basic Set Test
//

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
}


///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Set Test
//

TEST( ConcurrentSetTest )
{
    Concurrent::Set< Int > iset;
    TestBasicIntSet( iset );
}


///////////////////////////////////////////////////////////////////////////////
//
// Basic Set Snapshot Test
//

template< typename SetType >
void TestBasicSetWithSnapshot( SetType& set )
{
    auto snapshot = set.GetSnapshot();

    CHECK( snapshot.IsEmpty() );
}


///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Set with Snapshot Test
//

TEST( ConcurrentSetWithSnapshotTest )
{
    Concurrent::SetWithSnapshot< Int > iset;
    TestBasicSetWithSnapshot( iset );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE ConcurrentSetSuite

} // namespace Caramel

