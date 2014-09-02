// Caramel C++ Library Test - Meta - Range Suite

#include "CaramelTestPch.h"

#include <Caramel/Meta/Range.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( MetaRangeSuite )
{

enum RangeValue
{
    V_MIN = 0,
    V_MAX = 9,
    V_OUT = 10,
};


TEST( MetaRangeTest )
{
    typedef RangeN< Int, 0, 10 > D1;  // 1-digit number

    CHECK( false == D1::Contains( -1 ));
    CHECK( true  == D1::Contains( 0 ));
    CHECK( true  == D1::Contains( 9 ));
    CHECK( false == D1::Contains( 10 ));

    CHECK( true  == D1::Contains( V_MIN ));
    CHECK( true  == D1::Contains( V_MAX ));
    CHECK( false == D1::Contains( V_OUT ));


    typedef RangeN< RangeValue, V_MIN, V_OUT > R1;

    CHECK( false == R1::Contains( -1 ));
    CHECK( true  == R1::Contains( 0 ));
    CHECK( true  == R1::Contains( 9 ));
    CHECK( false == R1::Contains( 10 ));


    /// Range with only 1 element ///

    typedef RangeN< Int, 42, 43 > U1;

    CHECK( false == U1::Contains( 41 ));
    CHECK( true  == U1::Contains( 42 ));
    CHECK( false == U1::Contains( 43 ));


    /// Range with no element ///

    typedef RangeN< Int, 51, 51 > A1;

    CHECK( false == A1::Contains( 51 ));


    /// Range with Inverse Values - It should cause compiling error ///

    //typedef RangeN< Int, 9, 8 > E1;

    //CHECK( false == E1::Contains( 9 ));
}


} // SUITE MetaRangeSuite

} // namespace Caramel
