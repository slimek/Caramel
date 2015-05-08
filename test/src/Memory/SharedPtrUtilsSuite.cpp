// Caramel C++ Library Test - Memory - SharedPtr Utilities Suite

#include "CaramelTestPch.h"

#include <Caramel/Memory/SharedPtrUtils.h>


namespace Caramel
{

SUITE( SharedPtrUtils )
{

TEST( SharedPtrArithmetic )
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


//
// Substitute for Android NDK r9
//
TEST( SharedPtrAtomic )
{
    /// Load ///

    auto p1 = std::make_shared< Int >( 42 );

    auto p1c = AtomicLoad( &p1 );

    CHECK( *p1c == 42 );

    const std::shared_ptr< Int > cp1 = p1;

    // const std::shared_ptr should allow to load.
    auto cp1c = AtomicLoad( &cp1 );

    CHECK( *cp1c == 42 );


    /// Store ///

    auto p2 = std::make_shared< Int >( 51 );

    AtomicStore( &p1, p2 );

    CHECK( *p1 == 51 );
}


} // SUITE SharedPtrUtils

} // namespace Caramel
