// Caramel C++ Library Test - Lexical - Lexical Floating Suite

#include "CaramelTestPch.h"

#include <Caramel/Lexical/Floating.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( LexicalFloatingSuite )
{

TEST( LexicalFloatinTest )
{
    /// Float ///
    {
        Lexical::Floating< Float > lexFloat;

        CHECK( true == lexFloat.TryParse( "0" ));
        CHECK( 0 == lexFloat );

        CHECK( true == lexFloat.TryParse( "125" ));
        CHECK( 125 == lexFloat );

        CHECK( true == lexFloat.TryParse( "0.125" ));
        CHECK( 0.125 == lexFloat );

        CHECK( true == lexFloat.TryParse( "-2.5" ));
        CHECK( -2.5 == lexFloat );

        CHECK( false == lexFloat.TryParse( "Float" ));
        CHECK( false == lexFloat.TryParse( "2.5e" ));
        CHECK( false == lexFloat.TryParse( "a1.25" ));
    }

    /// Double ///
    {
        Lexical::Floating< Double > lexDouble;

        CHECK( true == lexDouble.TryParse( "0" ));
        CHECK( 0 == lexDouble );

        CHECK( true == lexDouble.TryParse( "125" ));
        CHECK( 125 == lexDouble );

        CHECK( true == lexDouble.TryParse( "0.125" ));
        CHECK( 0.125 == lexDouble );

        CHECK( true == lexDouble.TryParse( "-2.5" ));
        CHECK( -2.5 == lexDouble );

        CHECK( false == lexDouble.TryParse( "Float" ));
        CHECK( false == lexDouble.TryParse( "2.5e" ));
        CHECK( false == lexDouble.TryParse( "a1.25" ));
    }
}


} // SUITE LexicalFloatingSuite

} // namespace Caramel
