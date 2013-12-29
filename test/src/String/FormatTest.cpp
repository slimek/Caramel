// Caramel C++ Library Test - String - Format Test

#include "CaramelTestPch.h"

#include <Caramel/String/Format.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( FormatSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Format Test
//

TEST( FormatTrivialTest )
{
    CHECK( "" == Format( "" ));

    const Char alice1[] = "Alice";
    const Char* alice2 = "Alice";
    const std::string alice3( "Alice" );

    CHECK( "Alice" == Format( "Alice" ));
    CHECK( "Alice" == Format( alice1 ));
    CHECK( "Alice" == Format( alice2 ));
    CHECK( "Alice" == Format( alice3 ));
}


TEST( FormatIntegerTest )
{
    CHECK( "Score 0" == Format( "Score {0}", 0 ));

    CHECK( "Answer 1:42" == Format( "Answer {0}:{1}", 1, 42 ));
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE FormatSuite

} // namespace Caramel
