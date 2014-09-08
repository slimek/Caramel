// Caramel C++ Library Test - Document - INI Document Suite

#include "CaramelTestPch.h"

#include "Utils/StdVectorUtils.h"
#include <Caramel/Document/IniDocument.h>
#include <UnitTest++/UnitTest++.h>
#include <algorithm>
#include <functional>


namespace Caramel
{

SUITE( IniDocumentSuite )
{

TEST( IniDocumentFundamentalTest )
{
    IniDocument iniDoc( "../src/Document/test1.ini" );

    /// Booleans ///

    auto bools = iniDoc.GetSection( "Booleans" );

    CHECK( true  == bools.GetBool( "BoolTrue" ));
    CHECK( true  == bools.GetBool( "BoolTrueUpper" ));
    CHECK( true  == bools.GetBool( "BoolTrueCamel" ));
    CHECK( true  == bools.GetBool( "BoolTrueInt" ));
    CHECK( false == bools.GetBool( "BoolFalse" ));
    CHECK( false == bools.GetBool( "BoolFalseUpper" ));
    CHECK( false == bools.GetBool( "BoolFalseCamel" ));
    CHECK( false == bools.GetBool( "BoolFalseInt" ));

    CHECK_THROW( bools.GetBool( "BoolBad" ), Caramel::Exception );


    // As Integers
    CHECK( 1 == bools.GetInt( "BoolTrue" ));
    CHECK( 0 == bools.GetInt( "BoolFalse" ));
    CHECK( 1 == bools.GetUint( "BoolTrue" ));
    CHECK( 0 == bools.GetUint( "BoolFalse" ));

    // As String
    CHECK( "true"  == bools.GetString( "BoolTrue" ));
    CHECK( "false" == bools.GetString( "BoolFalse" ));


    /// Integers ///

    auto ints = iniDoc.GetSection( "Ints" );

    CHECK( 0 == ints.GetInt( "IntZero" ));
    CHECK( 1 == ints.GetInt( "IntOne" ));
    CHECK( 7 == ints.GetInt( "IntSeven" ));
    CHECK( INT_MAX == ints.GetInt( "IntIntMax" ));
    CHECK( -1 == ints.GetInt( "IntNegOne" ));
    CHECK( INT_MIN == ints.GetInt( "IntIntMin" ));

    CHECK( 1 == ints.GetInt( "IntHexOne" ));           // 0x1
    CHECK( 1 == ints.GetInt( "IntHexOneLong" ));       // 0x00000001
    CHECK( -1 == ints.GetInt( "IntHexNegOne" ));       // 0xffffffff
    CHECK( INT_MAX == ints.GetInt( "IntHexIntMax" ));  // 0x7fffffff
    CHECK( INT_MIN == ints.GetInt( "IntHexIntMin" ));  // 0x80000000
    CHECK( 15 == ints.GetInt( "IntHexFifteenUpper" )); // 0XF

    CHECK_THROW( ints.GetInt( "IntBad1" ), Caramel::Exception );
    CHECK_THROW( ints.GetInt( "IntBad2" ), Caramel::Exception );


    /// Unsigned Integers ///

    CHECK( 0 == ints.GetUint( "IntZero" ));
    CHECK( 1 == ints.GetUint( "IntOne" ));
    CHECK( 7 == ints.GetUint( "IntSeven" ));
    CHECK( INT_MAX == ints.GetUint( "IntIntMax" ));
    CHECK( UINT_MAX == ints.GetUint( "IntNegOne" ));
    CHECK( (Uint32)INT_MAX + 1 == ints.GetUint( "IntIntMin" ));

    CHECK( 1 == ints.GetUint( "IntHexOne" ));                      // 0x1
    CHECK( 1 == ints.GetUint( "IntHexOneLong" ));                  // 0x00000001
    CHECK( UINT_MAX == ints.GetUint( "IntHexNegOne" ));            // 0xffffffff
    CHECK( INT_MAX == ints.GetUint( "IntHexIntMax" ));             // 0x7fffffff
    CHECK( (Uint32)INT_MAX + 1 == ints.GetUint( "IntHexIntMin" )); // 0x80000000
    CHECK( 15 == ints.GetUint( "IntHexFifteenUpper" ));            // 0XF

    CHECK_THROW( ints.GetUint( "IntBad1" ), Caramel::Exception );
    CHECK_THROW( ints.GetUint( "IntBad2" ), Caramel::Exception );


    /// Get All Sections ///

    auto sections = iniDoc.GetAllSections();

    CHECK( 2 == sections.size() );

    SortBy( sections, std::mem_fn( &IniSection::GetName ));
    
    CHECK( "Booleans" == sections[0].GetName() );
    CHECK( "Ints" == sections[1].GetName() );
}


TEST( IniDocumentNamedValuesTest )
{
    IniDocument iniDoc( "../src/Document/test1.ini" );

    auto bools = iniDoc.GetSection( "Booleans" );
    const auto bnvs = bools.ToNamedValues();

    CHECK( true == bnvs["BoolTrue"].AsBool() );
    CHECK( true == bnvs["BoolTrueInt"].AsBool() );

    CHECK_THROW( bnvs["BoolBad"].AsBool(), Caramel::Exception );


    auto ints = iniDoc.GetSection( "Ints" );
    const auto invs = ints.ToNamedValues();

    CHECK( 0 == invs["IntZero"].AsInt() );
    CHECK( 2147483647 == invs["IntIntMax"].AsInt() );
}


} // SUITE IniDocumentSuite

} // namespace Caramel
