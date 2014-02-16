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


TEST( IntervalSetEraseTest )
{
    Concurrent::IntervalSet< Int > iset;
    iset.InsertClosed( 3, 10 );

    iset.Erase( 7 );
    CHECK( false == iset.Contains( 7 ));

    iset.EraseClosed( 8, 10 );
    CHECK( false == iset.IntersectsClosed( 7, 10 ));

    iset.EraseRightOpen( 1, 3 );  // No collision

    iset.EraseRightOpen( 3, 5 );
    CHECK( false == iset.IntersectsClosed( 3, 4 ));
    CHECK( true  == iset.ContainsClosed( 5, 6 ));

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

    iset.InsertClosed( 9, 12 );

    //
    // Contains must be in a continuous interval
    // [3, 6]-[9, 12] doesn't contain [3-12]
    //
    CHECK( false == iset.ContainsClosed( 3, 12 ));
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


TEST( IntervalSetLockedSetTest )
{
    /// Discrete Interval ///

    typedef Concurrent::IntervalSet< Int > IntSet;
    IntSet iset;

    iset.InsertClosed( 1, 5 );

    {
        IntSet::ConstLockedSet kset( iset );
        auto first = kset.Begin();

        typedef IntSet::IntervalType Interval;

        CHECK( Interval::closed( 1, 5 ) == *first );
    }
     
    
    /// Continuous Interval ///

    typedef Concurrent::IntervalSet< Double > DoubleSet;
    DoubleSet dset;

    dset.InsertClosed( 4, 13 );

    {
        DoubleSet::ConstLockedSet kset( dset );
        auto first = kset.Begin();

        typedef DoubleSet::IntervalType Interval;

        CHECK( Interval::closed( 4, 13 ) == *first );
    }    
}


TEST( IntervalSetSnapshotTest )
{
    Concurrent::IntervalSet< Int > iset;

    /// Empty ///

    auto shot1 = iset.GetSnapshot();

    CHECK( true == shot1.IsEmpty() );
    CHECK( 0    == shot1.Size() );

    /// With Closed Interval ///

    iset.InsertClosed( 1, 3 );
    iset.InsertClosed( 5, 7 );

    auto shot2 = iset.GetSnapshot();

    cout << "Size: " << shot2.Size() << endl;

    CHECK( false == shot2.IsEmpty() );
    CHECK( 2     == shot2.Size() );

    auto itv0 = shot2[0];

    CHECK( 1 == itv0.lower() );
    CHECK( 3 == itv0.upper() );
    CHECK( boost::icl::interval_bounds::closed() == itv0.bounds() );

    auto itv1 = shot2[1];

    CHECK( 5 == itv1.lower() );
    CHECK( 7 == itv1.upper() );
    CHECK( boost::icl::interval_bounds::closed() == itv1.bounds() );

    Concurrent::IntervalSet< Int > iset2;

    CHECK( true == iset2.Insert( shot2[0] ));

    iset2.InsertClosed( 6, 9 );

    CHECK( false == iset2.Insert( shot2[1] ));
    
    CHECK( true == iset2.ContainsClosed( 1, 3 ));
    CHECK( true == iset2.ContainsClosed( 5, 9 ));


    /// With Right Open Interval ///

    Concurrent::IntervalSet< Int > iset3;

    iset3.InsertRightOpen( 1, 3 );
    iset3.InsertRightOpen( 4, 6 );
    iset3.InsertClosed( 7, 9 );
    iset3.InsertRightOpen( 10, 12 );

    auto shot3 = iset3.GetSnapshot();

    CHECK( 3 == shot3.Size() );

    CHECK( boost::icl::interval_bounds::right_open() == shot3[0].bounds() );
    CHECK( boost::icl::interval_bounds::right_open() == shot3[1].bounds() );
    CHECK( boost::icl::interval_bounds::right_open() == shot3[2].bounds() );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE IntervalSetSuite

} // namespace Caramel
