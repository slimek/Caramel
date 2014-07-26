// Caramel C++ Library Test - Document - INI Document Suite

#include "CaramelTestPch.h"

#include <Caramel/Document/IniDocument.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( IniDocumentSuite )
{

TEST( IniDocumentFundamentalTest )
{
    IniDocument iniDoc( "../src/Document/test1.ini" );

    /// Booleans ///

    auto bools = iniDoc.GetSection( "Booleans" );

    CHECK( true  == bools.GetBoolValue( "BoolTrue" ));
    CHECK( true  == bools.GetBoolValue( "BoolTrueUpper" ));
    CHECK( true  == bools.GetBoolValue( "BoolTrueCamel" ));
    CHECK( true  == bools.GetBoolValue( "BoolTrueInt" ));
    CHECK( false == bools.GetBoolValue( "BoolFalse" ));
    CHECK( false == bools.GetBoolValue( "BoolFalseUpper" ));
    CHECK( false == bools.GetBoolValue( "BoolFalseCamel" ));
    CHECK( false == bools.GetBoolValue( "BoolFalseInt" ));

    CHECK_THROW( bools.GetBoolValue( "BoolBad" ), Caramel::Exception );


    // As Integers
    CHECK( 1 == bools.GetIntValue( "BoolTrue" ));
    CHECK( 0 == bools.GetIntValue( "BoolFalse" ));
    CHECK( 1 == bools.GetUintValue( "BoolTrue" ));
    CHECK( 0 == bools.GetUintValue( "BoolFalse" ));

    // As String
    CHECK( "true"  == bools.GetStringValue( "BoolTrue" ));
    CHECK( "false" == bools.GetStringValue( "BoolFalse" ));


    /// Integers ///

    auto ints = iniDoc.GetSection( "Ints" );

    CHECK( 0 == ints.GetIntValue( "IntZero" ));
    CHECK( 1 == ints.GetIntValue( "IntOne" ));
    CHECK( 7 == ints.GetIntValue( "IntSeven" ));
    CHECK( INT_MAX == ints.GetIntValue( "IntIntMax" ));
    CHECK( -1 == ints.GetIntValue( "IntNegOne" ));
    CHECK( INT_MIN == ints.GetIntValue( "IntIntMin" ));

    CHECK( 1 == ints.GetIntValue( "IntHexOne" ));           // 0x1
    CHECK( 1 == ints.GetIntValue( "IntHexOneLong" ));       // 0x00000001
    CHECK( -1 == ints.GetIntValue( "IntHexNegOne" ));       // 0xffffffff
    CHECK( INT_MAX == ints.GetIntValue( "IntHexIntMax" ));  // 0x7fffffff
    CHECK( INT_MIN == ints.GetIntValue( "IntHexIntMin" ));  // 0x80000000
    CHECK( 15 == ints.GetIntValue( "IntHexFifteenUpper" )); // 0XF

    CHECK_THROW( ints.GetIntValue( "IntBad1" ), Caramel::Exception );
    CHECK_THROW( ints.GetIntValue( "IntBad2" ), Caramel::Exception );


    /// Unsigned Integers ///

    CHECK( 0 == ints.GetUintValue( "IntZero" ));
    CHECK( 1 == ints.GetUintValue( "IntOne" ));
    CHECK( 7 == ints.GetUintValue( "IntSeven" ));
    CHECK( INT_MAX == ints.GetUintValue( "IntIntMax" ));
    CHECK( UINT_MAX == ints.GetUintValue( "IntNegOne" ));
    CHECK( (Uint32)INT_MAX + 1 == ints.GetUintValue( "IntIntMin" ));

    CHECK( 1 == ints.GetUintValue( "IntHexOne" ));                      // 0x1
    CHECK( 1 == ints.GetUintValue( "IntHexOneLong" ));                  // 0x00000001
    CHECK( UINT_MAX == ints.GetUintValue( "IntHexNegOne" ));            // 0xffffffff
    CHECK( INT_MAX == ints.GetUintValue( "IntHexIntMax" ));             // 0x7fffffff
    CHECK( (Uint32)INT_MAX + 1 == ints.GetUintValue( "IntHexIntMin" )); // 0x80000000
    CHECK( 15 == ints.GetUintValue( "IntHexFifteenUpper" ));            // 0XF

    CHECK_THROW( ints.GetUintValue( "IntBad1" ), Caramel::Exception );
    CHECK_THROW( ints.GetUintValue( "IntBad2" ), Caramel::Exception );
}


} // SUITE IniDocumentSuite

} // namespace Caramel
