// Caramel C++ Library - Precompiled Header Creator

#include "CaramelPch.h"

void CaramelPchDummy() {}


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Validation
//

/// Size of Fudamental Types ///

static_assert( 4 == sizeof( Int ),   "sizeof( Int ) should be 4" );
static_assert( 4 == sizeof( Uint ),  "sizeof( Uint ) should be 4" );


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
