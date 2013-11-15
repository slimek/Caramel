// Caramel C++ Library - Math Facility - Implementation

#include "CaramelPch.h"

#include <Caramel/Math/Floating.h>

#pragma warning( push )
#pragma warning( disable: 4819 )
#include <boost/math/special_functions/trunc.hpp>
#pragma warning( pop )


namespace Caramel
{

namespace Math
{

//
// Contents
//
//   Floating
//

///////////////////////////////////////////////////////////////////////////////
//
// Floating
//

//
// Truncation
//

Float  Trunc( Float  value ) { return boost::math::trunc( value ); }
Double Trunc( Double value ) { return boost::math::trunc( value ); }


///////////////////////////////////////////////////////////////////////////////

} // namespace Math

} // namespace Caramel
