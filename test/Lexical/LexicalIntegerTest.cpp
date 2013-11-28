// Caramel C++ Library Test - Lexical - Lexical Integer Test

#include "CaramelTestPch.h"

#include <Caramel/Lexical/Boolean.h>
#include <Caramel/Lexical/Integer.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( LexicalIntegerSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Lexical Integer Test
//

TEST( LexicalIntegerTest )
{
    /// Int32 ///
    {
        Lexical::Integer< Int32 > lexInt32;

        CHECK( true == lexInt32.TryParse( "123" ));
        CHECK( 123 == lexInt32 );

        CHECK( true == lexInt32.TryParse( "-456" ));
        CHECK( -456 == lexInt32 );

        CHECK( false == lexInt32.TryParse( "abc" ));
        CHECK( false == lexInt32.TryParse( "123.0" ));

        CHECK( true == lexInt32.TryParse( "0x0" ));
        CHECK( 0 == lexInt32 );

        CHECK( true == lexInt32.TryParse( "0x1" ));
        CHECK( 1 == lexInt32 );

        CHECK( true == lexInt32.TryParse( "0x7d" ));
        CHECK( 125 == lexInt32 );

        CHECK( true == lexInt32.TryParse( "0XFFFFFFFF" ));
        CHECK( -1 == lexInt32 );

        CHECK( false == lexInt32.TryParse( "0xFg" ));
    }


    /// Uint32 ///
    {
        Lexical::Integer< Uint32 > lexUint32;

        CHECK( true == lexUint32.TryParse( "123" ));
        CHECK( 123 == lexUint32 );

        CHECK( true == lexUint32.TryParse( "0x0" ));
        CHECK( 0 == lexUint32 );

        CHECK( true == lexUint32.TryParse( "0x1" ));
        CHECK( 1 == lexUint32 );

        CHECK( true == lexUint32.TryParse( "0x7d" ));
        CHECK( 125 == lexUint32 );

        CHECK( true == lexUint32.TryParse( "0XFFFFFFFF" ));
        CHECK( UINT32_MAX == lexUint32 );


        // Negative values would be cast to unsigned.

        CHECK( true == lexUint32.TryParse( "-456" ));
        CHECK(( UINT32_MAX - 455 ) == lexUint32 );
    }

    /// Int64 ///
    {
        Lexical::Integer< Int64 > lexInt64;

        CHECK( true == lexInt64.TryParse( "123" ));
        CHECK( 123 == lexInt64 );

        CHECK( true == lexInt64.TryParse( "0x0" ));
        CHECK( 0 == lexInt64 );

        CHECK( true == lexInt64.TryParse( "9223372036854775807" ));
        CHECK( INT64_MAX == lexInt64 );

        CHECK( true == lexInt64.TryParse( "0xFFFFFFFFFFFFFFFF" ));
        CHECK( -1 == lexInt64 );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Lexical Boolean Test
//

TEST( LexicalBooleanTest )
{
    Lexical::Boolean lexBool;

    /// Text ///

    CHECK( true == lexBool.TryParse( "true" ));
    CHECK( true == lexBool );

    CHECK( true == lexBool.TryParse( "True" ));
    CHECK( true == lexBool );

    CHECK( true == lexBool.TryParse( "TRUE" ));
    CHECK( true == lexBool );

    CHECK( true == lexBool.TryParse( "false" ));
    CHECK( false == lexBool );

    CHECK( true == lexBool.TryParse( "False" ));
    CHECK( false == lexBool );

    CHECK( true == lexBool.TryParse( "FALSE" ));
    CHECK( false == lexBool );

    CHECK( false == lexBool.TryParse( "Alice" ));
    CHECK( false == lexBool.TryParse( "" ));

    
    /// Integers ///

    CHECK( true == lexBool.TryParse( "0" ));
    CHECK( false == lexBool );

    CHECK( true == lexBool.TryParse( "1" ));
    CHECK( true == lexBool );

    CHECK( true == lexBool.TryParse( "125" ));
    CHECK( true == lexBool );

    CHECK( true == lexBool.TryParse( "-1" ));
    CHECK( true == lexBool );

    CHECK( true == lexBool.TryParse( "0x0" ));
    CHECK( false == lexBool );

    CHECK( true == lexBool.TryParse( "0x1" ));
    CHECK( true == lexBool );

    CHECK( true == lexBool.TryParse( "0xFF" ));
    CHECK( true == lexBool );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE LexicalIntegerSuite

} // namespace Caramel
