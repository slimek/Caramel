// Caramel C++ Library Test - Lexical - Lexical Integer Suite

#include "CaramelTestPch.h"

#include <Caramel/Lexical/Integer.h>


namespace Caramel
{

SUITE( LexicalInteger )
{

TEST( LexicalInteger )
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

        CHECK( true == lexInt64.TryParse( "0x8000000000000000" ));
        CHECK( INT64_MIN == lexInt64 );

        CHECK( true == lexInt64.TryParse( "0xFFFFFFFFFFFFFFFF" ));
        CHECK( -1 == lexInt64 );
    }

    /// Uint64 ///
    {
        Lexical::Integer< Uint64 > lexUint64;

        CHECK( true == lexUint64.TryParse( "123" ));
        CHECK( 123 == lexUint64 );

        CHECK( true == lexUint64.TryParse( "0x0" ));
        CHECK( 0 == lexUint64 );

        CHECK( true == lexUint64.TryParse( "9223372036854775807" ));
        CHECK( INT64_MAX == lexUint64 );

        CHECK( true == lexUint64.TryParse( "18446744073709551615" ));
        CHECK( UINT64_MAX == lexUint64 );

        CHECK( true == lexUint64.TryParse( "0xFFFFFFFFFFFFFFFF" ));
        CHECK( UINT64_MAX == lexUint64 );


        // Negative values would be cast to unsigned.

        CHECK( true == lexUint64.TryParse( "-456" ));
        CHECK(( UINT64_MAX - 455 ) == lexUint64 );
    }

    /// Int16 ///
    {
        Lexical::Integer< Int16 > lexInt16;

        CHECK( true == lexInt16.TryParse( "123" ));
        CHECK( 123 == lexInt16 );

        CHECK( true == lexInt16.TryParse( "-456" ));
        CHECK( -456 == lexInt16 );

        CHECK( true == lexInt16.TryParse( "32767" ));
        CHECK( 32767 == lexInt16 );

        CHECK( false == lexInt16.TryParse( "32768" ));

        CHECK( true == lexInt16.TryParse( "-32768" ));
        CHECK( -32768 == lexInt16 );
    }

    /// Uint16 ///
    {
        Lexical::Integer< Uint16 > lexUint16;

        CHECK( true == lexUint16.TryParse( "123" ));
        CHECK( 123 == lexUint16 );

        CHECK( false == lexUint16.TryParse( "-456" ));

        CHECK( true == lexUint16.TryParse( "65535" ));
        CHECK( 65535 == lexUint16 );

        CHECK( false == lexUint16.TryParse( "65536" ));
        
        CHECK( true == lexUint16.TryParse( "0x0" ));
        CHECK( 0 == lexUint16 );
    }
}


TEST( LexicalIntegerHex )
{
    /// Uint32 ///
    {
        Lexical::Integer< Uint32 > lexu;
        
        CHECK( true == lexu.TryParseHex( "0" ));
        CHECK( 0 == lexu );

        CHECK( true == lexu.TryParseHex( "1" ));
        CHECK( 1 == lexu );
        
        CHECK( true == lexu.TryParseHex( "FF" ));
        CHECK( 255 == lexu );
        
        CHECK( true == lexu.TryParseHex( "7f" ));
        CHECK( 127 == lexu );        

        CHECK( true == lexu.TryParseHex( "000000CD" ));
        CHECK( 205 == lexu );

        CHECK( false == lexu.TryParseHex( "0x1234" ));
    }
}


} // SUITE LexicalInteger

} // namespace Caramel
