// Caramel C++ Library Test - Value - Scalar Suite

#include "CaramelTestPch.h"

#include <Caramel/Value/Scalar.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( ScalarSuite )
{

TEST( ScalarTrivialTest )
{
    Scalar s;

    // Undef scalar should throws.
    CHECK_THROW( s.AsString(), Caramel::Exception );


    /// Boolean ///

    s.SetBool( true );

    CHECK( true   == s.AsBool() );
    CHECK( 1      == s.AsInt() );
    CHECK( "true" == s.AsString() );
}


} // SUITE ScalarSuite

} // namespace Caramel
