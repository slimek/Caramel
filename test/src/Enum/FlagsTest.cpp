// Caramel C++ Library Test - Enum - Flags Test

#include "CaramelTestPch.h"

#include <Caramel/Arithmetic/Flags.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( FlagsSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Flags Test
//

enum Flag
{
    F_0 = 0x01,  // bit 0
    F_1 = 0x02,  // bit 1
};


TEST( FlagsMatchTest )
{
    typedef Flags< F_1 > Fx01;

    CHECK( false == Fx01::MatchAny( 0 ));
    CHECK( true  == Fx01::MatchAny( 2 ));
    CHECK( true  == Fx01::MatchAny( 7 ));
    CHECK( false == Fx01::MatchAny( 8 ));

    CHECK( false == Fx01::MatchAll( 0 ));
    CHECK( true  == Fx01::MatchAll( 2 ));
    CHECK( true  == Fx01::MatchAll( 7 ));
    CHECK( false == Fx01::MatchAll( 8 ));


    typedef Flags< F_0 | F_1 > Fx02;

    CHECK( false == Fx02::MatchAny( 0 ));
    CHECK( true  == Fx02::MatchAny( 1 ));
    CHECK( true  == Fx02::MatchAny( 3 ));
    CHECK( false == Fx02::MatchAny( 4 ));

    CHECK( false == Fx02::MatchAll( 0 ));
    CHECK( false == Fx02::MatchAll( 1 ));
    CHECK( true  == Fx02::MatchAll( 3 ));
    CHECK( false == Fx02::MatchAll( 4 ));
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE FlagsSuite

} // namespace Caramel
