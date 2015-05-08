// Caramel C++ Library Test - String - Split Suite

#include "CaramelTestPch.h"

#include <Caramel/String/Split.h>


namespace Caramel
{

SUITE( Split )
{

TEST( SplitterFirst )
{
    SplitterFirst split1( "Alice.Margatroid", '.' );

    CHECK( split1 );
    CHECK( "Alice" == split1.before );
    CHECK( "Margatroid" == split1.after );


    SplitterFirst split2( "HomeSite/", '/' );

    CHECK( split2 );
    CHECK( "HomeSite" == split2.before );
    CHECK( ""         == split2.after );


    SplitterFirst split3( ">Beauty", '>' );

    CHECK( split3 );
    CHECK( ""       == split3.before );
    CHECK( "Beauty" == split3.after );


    SplitterFirst split4( "Touhou", 'x' );

    CHECK( ! split4 );
    CHECK( "Touhou" == split4.before );
    CHECK( ""       == split4.after );
}


} // SUITE Split

} // namespace Caramel
