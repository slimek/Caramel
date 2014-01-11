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
    iset.Add( 42 );
    CHECK( true == iset.Contains( 42 ));

    iset.AddClosed( 21, 28 );
    CHECK( false == iset.Contains( 20 ));
    CHECK( true  == iset.Contains( 21 ));
    CHECK( true  == iset.Contains( 25 ));
    CHECK( true  == iset.Contains( 28 ));
    CHECK( false == iset.Contains( 29 ));

    iset.AddRightOpen( 1, 8 );
    CHECK( false == iset.Contains( 0 ));
    CHECK( true  == iset.Contains( 1 ));
    CHECK( true  == iset.Contains( 5 ));
    CHECK( true  == iset.Contains( 7 ));
    CHECK( false == iset.Contains( 8 ));

    // Concatenation

    iset.AddRightOpen( 8, 10 );
    CHECK( true  == iset.Contains( 8 ));
    CHECK( false == iset.Contains( 10 ));

    iset.AddRightOpen( 11, 13 );
    CHECK( false == iset.Contains( 10 ));
    CHECK( true  == iset.Contains( 11 ));

    // Union

    iset.AddRightOpen( 0, 15 );
    CHECK( true  == iset.Contains( 10 ));

}


///////////////////////////////////////////////////////////////////////////////

} // SUITE IntervalSetSuite

} // namespace Caramel
