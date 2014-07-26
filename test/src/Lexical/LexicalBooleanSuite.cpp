// Caramel C++ Library Test - Lexical - Lexical Boolean Suite

#include "CaramelTestPch.h"

#include <Caramel/Lexical/Boolean.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( LexicalBooleanSuite )
{

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


} // SUITE LexicalBooleanSuite

} // namespace Caramel
