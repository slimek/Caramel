// Caramel C++ Library Test - Memory - SharedPtr Utilities Test

#include "CaramelTestPch.h"

#include <Caramel/Memory/SharedPtrUtils.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( SharedPtrUtilsSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Shared Ptr Utilities Test
//

TEST( SharedPtrArithmeticTest )
{
    /// Add/Substract with SharedPtr.

    auto i1 = std::make_shared< Int >( 42 );
    auto i2 = std::make_shared< Int >( 25 );
    auto i3 = std::make_shared< Int >( 3 );

    AddAssign( i1, i2 );
    CHECK( 67 == *i1 );

    SubstractAssign( i1, i3 );
    CHECK( 64 == *i1 );

    auto i1c1 = i1;

    AddAssign( i1, i2 );
    CHECK( 89 == *i1 );
    CHECK( 64 == *i1c1 );

    auto i1c2 = i1;

    SubstractAssign( i1, i3 );
    CHECK( 86 == *i1 );
    CHECK( 89 == *i1c2 );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE SharedPtrUtilsSuite

} // namespace Caramel
