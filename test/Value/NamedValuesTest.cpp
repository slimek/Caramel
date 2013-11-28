// Caramel C++ Library Test - Value - Named Values Test

#include "CaramelTestPch.h"

#include <Caramel/Value/NamedValues.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( NamedValuesSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Named Values Test
//

TEST( NamedValuesTest )
{
    NamedValues nv;
    const NamedValues& cnv = nv;

    const std::string marisa = "Marisa";

    nv[ "miko" ]    = "Reimu";
    nv[ "witch" ]   = marisa;
    nv[ "isRed" ]   = true;
    nv[ "isBlack" ] = false;
    nv[ "life" ]    = 3;
    nv[ "ratio" ]   = 1.15;
    nv[ "stage" ]   = -10;

    // With same type
    CHECK( "Reimu"  == nv[ "miko" ].AsString() );
    CHECK( "Marisa" == nv[ "witch" ].AsString() );
    CHECK( true     == nv[ "isRed" ].AsBool() );
    CHECK( false    == nv[ "isBlack" ].AsBool() );
    CHECK( 3        == nv[ "life" ].AsInt() );
    CHECK( 3        == nv[ "life" ].AsUint() );
    CHECK( 1.15     == nv[ "ratio" ].AsDouble() );
    CHECK( -10      == nv[ "stage" ].AsInt() );

    CHECK( "Reimu"  == cnv[ "miko" ].AsString() );
    CHECK( "Marisa" == cnv[ "witch" ].AsString() );
    CHECK( true     == cnv[ "isRed" ].AsBool() );
    CHECK( false    == cnv[ "isBlack" ].AsBool() );
    CHECK( 3        == cnv[ "life" ].AsInt() );
    CHECK( 3        == cnv[ "life" ].AsUint() );
    CHECK( 1.15     == cnv[ "ratio" ].AsDouble() );

    // With conversion
    //CHECK( "true"   == nv[ "isRed" ].AsString() );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE NamedValuesSuite

} // namespace Caramel
