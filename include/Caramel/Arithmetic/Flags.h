// Caramel C++ Library - Arithmetic Amenity - Flags Header

#ifndef __CARAMEL_ARITHMETIC_FLAGS_H
#define __CARAMEL_ARITHMETIC_FLAGS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Flags - A Helper class for matching integer flags.
//

template< Uint32 flags >
struct Flags
{
    static_assert( flags != 0, "Flags can't be zero" );

    static const Uint32 VALUE = flags;

    static Bool MatchAny( Uint32 testee ) { return ( VALUE & testee ) != 0; }
    static Bool MatchAll( Uint32 testee ) { return ( VALUE & testee ) == VALUE; }
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ARITHMETIC_FLAGS_H
