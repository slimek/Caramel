// Caramel C++ Library Test - String - Split Suite

#include "CaramelTestPch.h"

#include <Caramel/String/Split.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( SplitSuite )
{

TEST( SplitterFirstTest )
{
    SplitterFirst split1( "Alice.Margatroid", '.' );

    CHECK( true == split1 );
    CHECK( "Alice" == split1.before );
    CHECK( "Margatroid" == split1.after );


    SplitterFirst split2( "HomeSite/", '/' );

    CHECK( true == split2 );
    CHECK( "HomeSite" == split2.before );
    CHECK( ""         == split2.after );


    SplitterFirst split3( ">Beauty", '>' );

    CHECK( true == split3 );
    CHECK( ""       == split3.before );
    CHECK( "Beauty" == split3.after );


    SplitterFirst split4( "Touhou", 'x' );

    CHECK( false == split4 );
    CHECK( "Touhou" == split4.before );
    CHECK( ""       == split4.after );
}


} // SUITE SplitSuite

} // namespace Caramel
