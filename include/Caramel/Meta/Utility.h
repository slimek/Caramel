// Caramel C++ Library - Metaprogramming Amenity - Utility Header

#ifndef __CARAMEL_META_UTILITY_H
#define __CARAMEL_META_UTILITY_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Type of Specified Size
//

template< Uint size >
struct SizerN
{
    Char dummy[size];
};


///////////////////////////////////////////////////////////////////////////////
//
// Make of Type
// - This is a strawman function returns an instance of a type.
//

template< typename T > T MakeT();


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_META_UTILITY_H
