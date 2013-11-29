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

#if !defined( CARAMEL_SYSTEM_IS_IOS )

// NOTES: In Xcode we can't get the size of Long/Ulong. The reason is unknown yet...

static_assert( 4 == sizeof( Long ),  "sizeof( Long ) should be 4" );
static_assert( 4 == sizeof( Ulong ), "sizeof( Ulong ) should be 4" );

#endif


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
