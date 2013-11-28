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
    nv[ "missed" ]  = 0;

    // With same type
    CHECK( "Reimu"  == nv[ "miko" ].AsString() );
    CHECK( "Marisa" == nv[ "witch" ].AsString() );
    CHECK( true     == nv[ "isRed" ].AsBool() );
    CHECK( false    == nv[ "isBlack" ].AsBool() );
    CHECK( 3        == nv[ "life" ].AsInt() );
    CHECK( 3        == nv[ "life" ].AsUint() );
    CHECK( 1.15     == nv[ "ratio" ].AsDouble() );
    CHECK( -10      == nv[ "stage" ].AsInt() );
    CHECK( 0        == nv[ "missed" ].AsInt() );

    CHECK( "Reimu"  == cnv[ "miko" ].AsString() );
    CHECK( "Marisa" == cnv[ "witch" ].AsString() );
    CHECK( true     == cnv[ "isRed" ].AsBool() );
    CHECK( false    == cnv[ "isBlack" ].AsBool() );
    CHECK( 3        == cnv[ "life" ].AsInt() );
    CHECK( 3        == cnv[ "life" ].AsUint() );
    CHECK( 1.15     == cnv[ "ratio" ].AsDouble() );
    CHECK( 0        == cnv[ "missed" ].AsInt() );

    // Convert to Bool
    CHECK( true  == cnv[ "life" ].AsBool() );
    CHECK( true  == cnv[ "ratio" ].AsBool() );
    CHECK( false == cnv[ "missed" ].AsBool() );


    // Convert to String
    CHECK( "true"   == cnv[ "isRed" ].AsString() );
    CHECK( "false"  == cnv[ "isBlack" ].AsString() );
    CHECK( "3"      == cnv[ "life" ].AsString() );
    CHECK( "1.15"   == cnv[ "ratio" ].AsString() );
    CHECK( "-10"    == cnv[ "stage" ].AsString() );

    /// Convert from String ///

    nv[ "number1" ] = "1023";
    nv[ "number2" ] = "-375";
    nv[ "number3" ] = "3.1416";
    nv[ "yes" ] = "true";
    nv[ "no" ]  = "false";

    CHECK( 1023   == cnv[ "number1" ].AsInt() );
    CHECK( -375   == cnv[ "number2" ].AsInt() );
    CHECK( 3.1416 == cnv[ "number3" ].AsDouble() );
    CHECK( true   == cnv[ "yes" ].AsBool() );
    CHECK( false  == cnv[ "no" ].AsBool() );


    /// Short Integers ///

    const Int16  i16max = INT16_MAX;
    const Uint16 u16max = UINT16_MAX;

    nv[ "i16max" ] = i16max;
    nv[ "u16max" ] = u16max;

    CHECK( 32767 == cnv[ "i16max" ].AsInt() );
    CHECK( 65535 == cnv[ "u16max" ].AsInt() );

}


///////////////////////////////////////////////////////////////////////////////

} // SUITE NamedValuesSuite

} // namespace Caramel
