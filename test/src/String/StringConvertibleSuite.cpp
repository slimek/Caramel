// Caramel C++ Library Test - String - String Convertible Suite

#include "CaramelTestPch.h"

#include <Caramel/String/StringConvertible.h>
#include <Caramel/Value/Scalar.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

//
// NOTES:
//   We use Scalar, which inherits StringConvertible, as the test case.
//

SUITE( StringConvertibleSuite )
{

TEST( StringConvertibleComparisonTest )
{
    Scalar alice( "Alice" );

    
    /// Equality ///

    CHECK( alice   == "Alice" );
    CHECK( "Alice" == alice );

    CHECK( alice   != "Reimu" );
    CHECK( "Reimu" != alice );
}


} // SUITE StringConvertibleSuite


} // namespace Caramel
