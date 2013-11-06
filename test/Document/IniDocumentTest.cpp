// Caramel C++ Library Test - Document - INI Document Test

#include "CaramelTestPch.h"

#include <Caramel/Document/IniDocument.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( IniDocumentSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// INI Document Test
//

TEST( IniDocumentFundamentalTest )
{
    IniDocument iniDoc( "Document\\test1.ini" );

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
    CHECK( 1 == ints.GetIntValue( "IntHexOne" ));           // 0x1
    CHECK( 1 == ints.GetIntValue( "IntHexOneLong" ));       // 0x00000001
    CHECK( INT_MAX == ints.GetIntValue( "IntHexIntMax" ));  // 0x7FFFFFFF

    CHECK_THROW( ints.GetIntValue( "IntBad" ), Caramel::Exception );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE IniDocumentSuite

} // namespace Caramel
