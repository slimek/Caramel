// Caramel C++ Library - Random Facility - Uniform Random Header

#ifndef __CARAMEL_RANDOM_UNIFORM_RANDOM_H
#define __CARAMEL_RANDOM_UNIFORM_RANDOM_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


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


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_RANDOM_UNIFORM_RANDOM_H