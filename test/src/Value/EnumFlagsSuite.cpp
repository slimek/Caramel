// Caramel C++ Library Test - Value - Enum Flags Suite

#include "CaramelTestPch.h"

#include <Caramel/Value/EnumFlags.h>


namespace Caramel
{

SUITE( EnumFlagsSuite )
{

enum ColorFlag
{
    COLOR_NONE  = 0,
    COLOR_RED   = 0x01,
    COLOR_GREEN = 0x02,
    COLOR_BLUE  = 0x04,

    COLOR_YELLOW = COLOR_RED | COLOR_GREEN,
};


TEST( EnumFlagsTest )
{
    EnumFlags< ColorFlag > none;

    CHECK( false == none.Match( COLOR_RED ));
    CHECK( false == none.Match( COLOR_GREEN ));
    CHECK( false == none.Match( COLOR_YELLOW ));
    CHECK( false == none.Match( COLOR_BLUE ));

    EnumFlags< ColorFlag > red( COLOR_RED );

    CHECK( true  == red.Match( COLOR_RED ));
    CHECK( false == red.Match( COLOR_GREEN ));
    CHECK( false == red.Match( COLOR_YELLOW ));
    CHECK( false == red.Match( COLOR_BLUE ));

    EnumFlags< ColorFlag > yellow( { COLOR_RED, COLOR_GREEN } );

    CHECK( true  == yellow.Match( COLOR_RED ));
    CHECK( true  == yellow.Match( COLOR_GREEN ));
    CHECK( true  == yellow.Match( COLOR_YELLOW ));
    CHECK( false == yellow.Match( COLOR_BLUE ));
}

} // SUITE EnumFlagsSuite

} // namespace Caramel
