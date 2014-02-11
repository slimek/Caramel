// Caramel C++ Library Test - Concurrent - Queue Test

#include "CaramelTestPch.h"

#include <Caramel/Concurrent/Queue.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( ConcurrentQueueSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Queue Test
//

TEST( ConcurrentQueueTrivialTest )
{
    Concurrent::Queue< Int > ique;
    Int value = 0;

    CHECK( true  == ique.IsEmpty() );
    CHECK( 0     == ique.Size() );
    CHECK( false == ique.TryPop( value ));

    ique.Push( 42 );

    CHECK( false == ique.IsEmpty() );
    CHECK( 1     == ique.Size() );
    CHECK( true  == ique.TryPop( value ));
    CHECK( 42 == value );

    CHECK( true  == ique.IsEmpty() );
    CHECK( 0     == ique.Size() );
    CHECK( false == ique.TryPop( value ));

    ique.Push( 16 );
    ique.Push( 64 );
    ique.Push( 256 );

    CHECK( false == ique.IsEmpty() );
    CHECK( 3     == ique.Size() );

    ique.Clear();

    CHECK( true == ique.IsEmpty() );
    CHECK( 0    == ique.Size() );
}


TEST( ConcurrentQueueSnapshotTest )
{
    Concurrent::QueueWithSnapshot< Int > ique;
    Int value = 0;

    auto sp0 = ique.GetSnapshot();

    CHECK( true == sp0.IsEmpty() );
    CHECK( 0 == sp0.Size() );

    ique.Push( 16 );
    ique.Push( 64 );
    ique.Push( 256 );

    auto sp1 = ique.GetSnapshot();

    CHECK( false == sp1.IsEmpty() );
    CHECK( 3 == sp1.Size() );
    CHECK( 16 == sp1[0] );
    CHECK( 64 == sp1[1] );
    CHECK( 256 == sp1[2] );

    Int sum = 0;
    for ( Int v : sp1 )
    {
        sum += v;
    }
    CHECK( 336 == sum );

    CHECK( true == ique.TryPop( value ));

    auto sp2 = ique.GetSnapshot();

    CHECK( false == sp2.IsEmpty() );
    CHECK( 2 == sp2.Size() );
    CHECK( 64 == sp2[0] );
    CHECK( 256 == sp2[1] );

    ique.Clear();

    auto sp3 = ique.GetSnapshot();

    //CHECK( true == sp3.IsEmpty() );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE( ConcurrentQueueSuite )

} // namespace Caramel
