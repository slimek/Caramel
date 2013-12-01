// Caramel C++ Library - Random Facility - Uniform Random Header

#ifndef __CARAMEL_RANDOM_UNIFORM_RANDOM_H
#define __CARAMEL_RANDOM_UNIFORM_RANDOM_H
#pragma once

#include <Caramel/Caramel.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Uniform Random Distribution
//

//
// Generate Random Integers
// - Generate values between 'minValue' and 'maxValue' (inclusive).
//   This function is thread-safe.
//
//   EXAMPLE:
//
//   If you want a dice ( 1 to 6 ), call this:
//
//       GenRandomUint( 1, 6 );
//

Int  GenRandomInt ( Int  minValue, Int  maxValue );
Uint GenRandomUint( Uint minValue, Uint maxValue );


//
// Generate Random Floatings
// - Generate values between 'lowerBound' and 'upperBound' (exclusive? see below).
//   This function is thread-safe.
//
//   EXAMPLE:
//
//   If you call this:
//
//       GenRandomFloat( 0, 1 );
//
//   You will get a value from 0 to very close to 1, but ...
//   It may or may not returns 1, it depends on the precision and compiler implementations.
//

Float GenRandomFloat( Float lowerBound, Float upperBound );


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_RANDOM_UNIFORM_RANDOM_H
