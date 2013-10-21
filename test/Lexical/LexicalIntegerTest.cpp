// Caramel C++ Library Test - Lexical - Lexical Integer Test

#include "CaramelTestPch.h"

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
    }


    /// Uint32 ///
    {
        Lexical::Integer< Uint32 > lexUint32;

        CHECK( true == lexUint32.TryParse( "123" ));
        CHECK( 123 == lexUint32 );

        CHECK( true == lexUint32.TryParse( "-456" ));
        CHECK(( 0xFFFFFFFF - 455 ) == lexUint32 );
    }
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE LexicalIntegerSuite

} // namespace Caramel
