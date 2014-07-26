// Caramel C++ Library Test - Numeric - Union Bits Suite

#include "CaramelTestPch.h"

#include <Caramel/Numeric/UnionBits.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( UnionBitsSuite )
{

TEST( UnionBits16Test )
{
    UnionBits16 b16;
    b16.i = 0x1234;

    CHECK( 0x1234 == b16.ui );
    CHECK( 0x34   == b16.bs[0] );
    CHECK( 0x12   == b16.bs[1] );
    CHECK( 0x34   == b16.bb.lo );
    CHECK( 0x12   == b16.bb.hi );
}


TEST( UnionBits32Test )
{
    UnionBits32 b32;
    b32.i = 0x12345678;

    CHECK( 0x12345678u == b32.ui );

    // Bytes
    CHECK( 0x78 == b32.bs[0] );
    CHECK( 0x56 == b32.bs[1] );
    CHECK( 0x34 == b32.bs[2] );
    CHECK( 0x12 == b32.bs[3] );

    // Qu-Byte
    CHECK( 0x78 == b32.qb.lo );
    CHECK( 0x56 == b32.qb.ml );
    CHECK( 0x34 == b32.qb.mh );
    CHECK( 0x12 == b32.qb.hi );

    // Bi-Bits16
    CHECK( 0x5678 == b32.bb16.lo.ui );
    CHECK( 0x1234 == b32.bb16.hi.ui );


    /// Floating from/to Binary Presentation ///

    UnionBits32 f32;
    f32.ui = 0x3F800000;

    CHECK( 1.0f == f32.f );

    f32.f = -1.0f;

    CHECK( 0xBF800000u == f32.ui );
}


} // SUITE UnionBitsSuite

} // namespace Caramel
