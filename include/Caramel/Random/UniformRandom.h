// Caramel C++ Library - Random Facility - Uniform Random Header

#ifndef __CARAMEL_RANDOM_UNIFORM_RANDOM_H
#define __CARAMEL_RANDOM_UNIFORM_RANDOM_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Uniform Random Distribution
//

//
// Generate Random Integers
// - Generate values between 'minValue' and 'maxValue' (inclusive).
//   These functions are thread-safe.
//
//   EXAMPLE:
//
//   If you want a dice ( 1 to 6 ), call this:
//
//       GenRandomUint( 1, 6 );
//

Int    GenRandomInt   ( Int    minValue, Int    maxValue );
Uint   GenRandomUint  ( Uint   minValue, Uint   maxValue );
Uint64 GenRandomUint64( Uint64 minValue, Uint64 maxValue );

Usize GenRandomUsize( Usize minValue, Usize maxValue );  // for std::size_t


//
// Generate Random Floatings
// - Generate values between 'lowerBound' and 'upperBound' (exclusive? see below).
//   These functions are thread-safe.
//
//   EXAMPLE:
//
//   If you call this:
//
//       GenRandomFloat( 0, 1 );
//
//   You will get a value from 0 to very close to 1, but ...
//   It may or may not returns 1, which depends on the precision and compiler implementations.
//

Float  GenRandomFloat ( Float  lowerBound, Float  upperBound );
Double GenRandomDouble( Double lowerBound, Double upperBound );


//
// Generate Random Boolean
// - Generate a boolen with a given probability.
//   1.0 to always true, and 0.0 to always false.
//

Bool GenRandomBool( Double prob );


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_RANDOM_UNIFORM_RANDOM_H
