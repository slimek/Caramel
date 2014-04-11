// Caramel C++ Library - Arithmetic Amenity - Power of Two Header

#ifndef __CARAMEL_ARITHMETIC_POWER_OF_TWO_H
#define __CARAMEL_ARITHMETIC_POWER_OF_TWO_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Is Power of Two Predicates
//
//   In fact, these predicates check if an integer value has only one "1" bit
//   in its binary form.
//
//   Almost all NEGATIVE integers are NOT power of two, except for the min value.
//   For example:
//
//      16-bit Int 0x8000 (-32768) would be power of two.
//   

//
// Preprocesser Primitive
//

#define CARAMEL_IS_POWER_OF_TWO( n ) (( 0 != n ) && ( 0x0 == ( n & n - 1 )))


//
// Compile-time Expression
//

template< Uint n >
struct IsPowerOfTwoN : public BoolType< CARAMEL_IS_POWER_OF_TWO( n ) >
{};


//
// Runtime Function
//

template< typename Integer >
inline Bool IsPowerOfTwo( Integer value )
{
    return CARAMEL_IS_POWER_OF_TWO( value );    
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ARITHMETIC_POWER_OF_TWO_H
