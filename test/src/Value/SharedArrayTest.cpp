// Caramel C++ Library Test - Value - Shared Array Test

#include "CaramelTestPch.h"

#include <Caramel/Value/SharedArray.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( SharedArraySuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Shared Array Test
//

TEST( ConstSharedArrayTest )
{
    ConstSharedArray< Int > ia0;
    
    CHECK( true  == ia0.IsEmpty() );
    CHECK( 0     == ia0.Size() );
    CHECK( false == ia0.Contains( 42 ));
    CHECK( ia0.Begin() == ia0.End() );

    ConstSharedArray< Int > ia1( 1 );

    CHECK( false == ia1.IsEmpty() );
    CHECK( 1     == ia1.Size() );
    CHECK( ia1.Begin() + 1 == ia1.End() );
}


TEST( SharedArrayTest )
{
    SharedArray< std::string > sa0;

    CHECK( true   == sa0.IsEmpty() );
    CHECK( 0      == sa0.Size() );
    CHECK( false  == sa0.Contains( "Cirno" ));
    CHECK( sa0.Begin() == sa0.End() );

    SharedArray< std::string > sa( 3 );

    CHECK( false  == sa.IsEmpty() );
    CHECK( 3      == sa.Size() );
    CHECK( ""     == sa[0] );

    sa[0] = "Alice";
    sa[1] = "Reimu";
    sa[2] = "Marisa";

    CHECK( "Alice" == sa[0] );

    auto iter = sa.Begin();
    *( ++ iter) = "Suika";
    CHECK( "Suika" == sa[1] );

    sa.Reset( 5 );

    CHECK( 5  == sa.Size() );
    CHECK( "" == sa[1] );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE( SharedArraySuite )

} // namespace Caramel
