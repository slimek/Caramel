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

TEST( NamedValuesTrivialTest )
{
    NamedValues nv;

    CHECK( true == nv.IsEmpty() );
    CHECK( 0    == nv.Size() );

    auto values = nv.GetValueMap();

    CHECK( true == values.empty() );
    CHECK( 0    == values.size() );
}


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
    nv[ "score" ]   = INT64_MAX;
    nv[ "hiscore" ] = UINT64_MAX;

    // With same type
    CHECK( "Reimu"    == nv[ "miko" ].AsString() );
    CHECK( "Marisa"   == nv[ "witch" ].AsString() );
    CHECK( true       == nv[ "isRed" ].AsBool() );
    CHECK( false      == nv[ "isBlack" ].AsBool() );
    CHECK( 3          == nv[ "life" ].AsInt() );
    CHECK( 3          == nv[ "life" ].AsUint() );
    CHECK( 1.15       == nv[ "ratio" ].AsDouble() );
    CHECK( -10        == nv[ "stage" ].AsInt() );
    CHECK( 0          == nv[ "missed" ].AsInt() );
    CHECK( INT64_MAX  == nv[ "score" ].AsInt64() );
    CHECK( UINT64_MAX == nv[ "hiscore" ].AsUint64() );

    CHECK( "Reimu"    == cnv[ "miko" ].AsString() );
    CHECK( "Marisa"   == cnv[ "witch" ].AsString() );
    CHECK( true       == cnv[ "isRed" ].AsBool() );
    CHECK( false      == cnv[ "isBlack" ].AsBool() );
    CHECK( 3          == cnv[ "life" ].AsInt() );
    CHECK( 3          == cnv[ "life" ].AsUint() );
    CHECK( 1.15       == cnv[ "ratio" ].AsDouble() );
    CHECK( 0          == cnv[ "missed" ].AsInt() );
    CHECK( INT64_MAX  == cnv[ "score" ].AsInt64() );
    CHECK( UINT64_MAX == cnv[ "hiscore" ].AsUint64() );

    // Convert to Bool
    CHECK( true  == cnv[ "life" ].AsBool() );
    CHECK( true  == cnv[ "ratio" ].AsBool() );
    CHECK( false == cnv[ "missed" ].AsBool() );
    CHECK( true  == cnv[ "score" ].AsBool() );

    // Convert to Double
    CHECK( 1.0   == cnv[ "isRed" ].AsDouble() );
    CHECK( 3.0   == cnv[ "life" ].AsDouble() );
    CHECK( -10.0 == cnv[ "stage" ].AsDouble() );
    CHECK( static_cast< Double >( INT64_MAX ) == cnv[ "score" ].AsDouble() );

    // Convert to String
    CHECK( "true"   == cnv[ "isRed" ].AsString() );
    CHECK( "false"  == cnv[ "isBlack" ].AsString() );
    CHECK( "3"      == cnv[ "life" ].AsString() );
    CHECK( "1.15"   == cnv[ "ratio" ].AsString() );
    CHECK( "-10"    == cnv[ "stage" ].AsString() );
    CHECK( "9223372036854775807" == cnv[ "score" ].AsString() );

    /// Convert from String ///

    nv[ "number1" ] = "1023";
    nv[ "number2" ] = "-375";
    nv[ "number3" ] = "3.1416";
    nv[ "yes" ] = "true";
    nv[ "no" ]  = "false";
    nv[ "bigNumber" ] = "12345678900";

    CHECK( 1023   == cnv[ "number1" ].AsInt() );
    CHECK( -375   == cnv[ "number2" ].AsInt() );
    CHECK( 3.1416 == cnv[ "number3" ].AsDouble() );
    CHECK( true   == cnv[ "yes" ].AsBool() );
    CHECK( false  == cnv[ "no" ].AsBool() );
    CHECK( 12345678900LL == cnv[ "bigNumber" ].AsInt64() );


    /// Short Integers ///

    const Int16  i16max = INT16_MAX;
    const Uint16 u16max = UINT16_MAX;

    nv[ "i16max" ] = i16max;
    nv[ "u16max" ] = u16max;

    CHECK( 32767 == cnv[ "i16max" ].AsInt() );
    CHECK( 65535 == cnv[ "u16max" ].AsInt() );


    /// Long Integers - Treats long as int32 ///

    const Long  lmax  = INT32_MAX;
    const Ulong ulmax = UINT32_MAX;

    nv[ "lmax" ]  = lmax;
    nv[ "ulmax" ] = ulmax;

    CHECK( INT32_MAX  == cnv[ "lmax" ].AsInt() );
    CHECK( UINT32_MAX == cnv[ "ulmax" ].AsUint() );
}


TEST( NameValuesValueMapTest )
{
    NamedValues nv;

    nv[ "Alice" ]  = "doll master";
    nv[ "Reimu" ]  = "miko";
    nv[ "Marisa" ] = "witch";

    CHECK( false == nv.IsEmpty() );
    CHECK( 3     == nv.Size() );

    const auto values = nv.GetValueMap();

    auto iv = values.begin();
    CHECK( "Alice" == iv->first && "doll master" == iv->second );

    ++ iv;
    CHECK( "Marisa" == iv->first && "witch" == iv->second );

    ++ iv;
    CHECK( "Reimu" == iv->first && "miko" == iv->second );

    ++ iv;
    CHECK( values.end() == iv );
}


TEST( NamedValuesChainTest )
{
    auto nv = NamedValues
        ( "Chirno", 123 )
        ( "Mystia", "Lorelei" )
        ( "Kogasa", 3.14 )
        ( "Parsee", false )
        ( "Hina",   INT64_MAX );

    CHECK( 123       == nv[ "Chirno" ].AsInt() );
    CHECK( "Lorelei" == nv[ "Mystia" ].AsString() );
    CHECK( 3.14      == nv[ "Kogasa" ].AsDouble() );
    CHECK( false     == nv[ "Parsee" ].AsBool() );
    CHECK( INT64_MAX == nv[ "Hina" ].AsInt64() );
}


TEST( NamedValuesFromMapTest )
{
    std::map< std::string, std::string > smap;
    smap[ "Alice"  ] = "doll master";
    smap[ "Marisa" ] = "witch";
    smap[ "Reimu"  ] = "miko";

    const NamedValues nv( smap );

    CHECK( "doll master" == nv[ "Alice" ].AsString() );
    CHECK( "witch"       == nv[ "Marisa" ].AsString() );
    CHECK( "miko"        == nv[ "Reimu" ].AsString() );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE NamedValuesSuite

} // namespace Caramel
