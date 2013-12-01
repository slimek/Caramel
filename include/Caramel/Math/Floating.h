// Caramel C++ Library - Math Facility - Floating Header

#ifndef __CARAMEL_MATH_FLOATING_H
#define __CARAMEL_MATH_FLOATING_H
#pragma once

#include <Caramel/Caramel.h>


namespace Caramel
{

namespace Math
{

///////////////////////////////////////////////////////////////////////////////
//
// Truncation Functions
//

Float  Trunc( Float  value );
Double Trunc( Double value );

template< typename T > T Trunc( T );  // Block any other types.


///////////////////////////////////////////////////////////////////////////////

} // namespace Math

} // namespace Caramel

#endif // __CARAMEL_MATH_FLOATING_H
