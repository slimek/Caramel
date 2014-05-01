// Caramel C++ Library - Arithmetic Amenity - Flags Header

#ifndef __CARAMEL_ARITHMETIC_FLAGS_H
#define __CARAMEL_ARITHMETIC_FLAGS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Flags - A Helper class for flags operation
//

template< Uint32 flags >
struct Flags
{
    static_assert( 0 < flags, "Flags can't be zero" );

    static const Uint32 VALUE = flags;

    static Bool MatchAny( Uint32 testee ) { return 0     != ( VALUE & testee ); }
    static Bool MatchAll( Uint32 testee ) { return VALUE == ( VALUE & testee ); }
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ARITHMETIC_FLAGS_H
