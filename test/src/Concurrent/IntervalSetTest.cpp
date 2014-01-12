// Caramel C++ Library Test - Concurrent - Interval Set Test

#include "CaramelTestPch.h"

#include <Caramel/Concurrent/IntervalSet.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( IntervalSetSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Interval Set
//

TEST( IntervalSetTest )
{
    Concurrent::IntervalSet< Int > iset;

    CHECK( false == iset.Contains( 42 ));
    iset.Insert( 42 );
    CHECK( true == iset.Contains( 42 ));

    iset.InsertClosed( 21, 28 );
    CHECK( false == iset.Contains( 20 ));
    CHECK( true  == iset.Contains( 21 ));
    CHECK( true  == iset.Contains( 25 ));
    CHECK( true  == iset.Contains( 28 ));
    CHECK( false == iset.Contains( 29 ));

    iset.InsertRightOpen( 1, 8 );
    CHECK( false == iset.Contains( 0 ));
    CHECK( true  == iset.Contains( 1 ));
    CHECK( true  == iset.Contains( 5 ));
    CHECK( true  == iset.Contains( 7 ));
    CHECK( false == iset.Contains( 8 ));

    // Concatenation

    iset.InsertRightOpen( 8, 10 );
    CHECK( true  == iset.Contains( 8 ));
    CHECK( false == iset.Contains( 10 ));

    iset.InsertRightOpen( 11, 13 );
    CHECK( false == iset.Contains( 10 ));
    CHECK( true  == iset.Contains( 11 ));

    // Union

    iset.InsertRightOpen( 0, 15 );
    CHECK( true  == iset.Contains( 10 ));
}


TEST( IntervalSetInsertTest )
{
    Concurrent::IntervalSet< Int > iset;

    CHECK( true  == iset.InsertClosed( 3, 6 ));
    CHECK( false == iset.InsertClosed( 4, 8 ));
    CHECK( true  == iset.ContainsClosed( 3, 8 ));

    CHECK( true  == iset.InsertRightOpen( 1, 3 ));
    CHECK( true  == iset.ContainsClosed( 1, 8 ));
    
    CHECK( true  == iset.InsertRightOpen( 9, 12 ));
    CHECK( true  == iset.ContainsClosed( 1, 11 ));
}


TEST( IntervalSetContainsTest )
{
    // The sub-interval must be totally within a valid interval.

    Concurrent::IntervalSet< Int > iset;
    iset.InsertClosed( 3, 6 );

    CHECK( true  == iset.ContainsClosed( 3, 6 ));
    CHECK( true  == iset.ContainsClosed( 4, 5 ));
    CHECK( true  == iset.ContainsClosed( 5, 5 ));
    CHECK( false == iset.ContainsClosed( 2, 4 ));
    CHECK( false == iset.ContainsClosed( 5, 7 ));

    CHECK( true  == iset.ContainsRightOpen( 3, 7 ));
}


TEST( IntervalSetIntersectsTest )
{
    Concurrent::IntervalSet< Int > iset;
    iset.InsertClosed( 3, 6 );

    CHECK( true  == iset.IntersectsClosed( 3, 6 ));
    CHECK( true  == iset.IntersectsClosed( 4, 5 ));
    CHECK( true  == iset.IntersectsClosed( 5, 5 ));
    CHECK( true  == iset.IntersectsClosed( 2, 4 ));
    CHECK( true  == iset.IntersectsClosed( 5, 7 ));
    CHECK( true  == iset.IntersectsClosed( 1, 3 ));
    CHECK( false == iset.IntersectsClosed( 1, 2 ));
    CHECK( false == iset.IntersectsClosed( 7, 8 ));

    CHECK( true  == iset.IntersectsRightOpen( 3, 7 ));
    CHECK( true  == iset.IntersectsRightOpen( 2, 4 ));
    CHECK( true  == iset.IntersectsRightOpen( 5, 7 ));
    CHECK( false == iset.IntersectsRightOpen( 1, 3 ));
    CHECK( true  == iset.IntersectsRightOpen( 6, 8 ));
    CHECK( false == iset.IntersectsRightOpen( 7, 8 ));
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE IntervalSetSuite

} // namespace Caramel
