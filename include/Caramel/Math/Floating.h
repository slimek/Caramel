// Caramel C++ Library - Math Facility - Floating Header

#ifndef __CARAMEL_MATH_FLOATING_H
#define __CARAMEL_MATH_FLOATING_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

namespace Math
{

///////////////////////////////////////////////////////////////////////////////
//
// Truncation Functions
// - Round to zero. For example:
//     3.7  ->  3
//    -4.6  ->  4
//

Float  Trunc( Float  value );
Double Trunc( Double value );

template< typename T > T Trunc( T );  // Block any other types.


///////////////////////////////////////////////////////////////////////////////

} // namespace Math

} // namespace Caramel

#endif // __CARAMEL_MATH_FLOATING_H
