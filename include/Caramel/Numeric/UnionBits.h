// Caramel C++ Library - Numeric Amenity - Union Bits Header

#ifndef __CARAMEL_NUMERIC_UNION_BITS_H
#define __CARAMEL_NUMERIC_UNION_BITS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

////////////////////////////////////////////////////////////////////////////
//
// Union Bits
// - Fundamental types compound.
//   
//   ATTENTION:
//     Current implementation only works in little endian architectures.
//
//   TODO:
//     After the Boost is upgraded to v1.55 or higher,
//     use Boost.Predef macro BOOST_ENDIAN_LITTLE_BYTE to verify the endian.
//

//
// 16 Bits
//

// Components
struct CompBiByte { Byte lo, hi; };  // Low, High

union UnionBits16
{
    Int16   i;
    Uint16  ui;
    Byte    bs[2];

    CompBiByte bb;
};


//
// 32 Bits
//

// Components
struct CompQuByte { Byte lo, ml, mh, hi; };  // Low, Middle-low, Middle-high, High
struct CompBiBits16 { UnionBits16 lo, hi; };

union UnionBits32
{
    Int32   i;
    Uint32  ui;
    Float   f;
    Byte    bs[4];

    CompQuByte   qb;
    CompBiBits16 bb16;
};


//
// Verification
//

static_assert( 2 == sizeof( UnionBits16 ), "UnionBits16 should be 16-bit" );
static_assert( 4 == sizeof( UnionBits32 ), "UnionBits32 should be 32-bit" );


////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_NUMERIC_UNION_BITS_H
