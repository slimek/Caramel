// Caramel C++ Library Test - String - String Convertible Suite

#include "CaramelTestPch.h"

#include <Caramel/String/StringConvertible.h>
#include <Caramel/Value/Scalar.h>


namespace Caramel
{

//
// NOTES:
//   We use Scalar, which inherits StringConvertible, as the test case.
//

SUITE( StringConvertible )
{

TEST( StringConvertibleComparison )
{
    Scalar alice( "Alice" );

    
    /// Equality ///

    CHECK( alice   == "Alice" );
    CHECK( "Alice" == alice );

    CHECK( alice   != "Reimu" );
    CHECK( "Reimu" != alice );
}


} // SUITE StringConvertible


} // namespace Caramel
