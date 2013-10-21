// Caramel C++ Library - Metaprogramming Amenity - Integral Types Header

#ifndef __CARAMEL_META_INTEGRAL_TYPES_H
#define __CARAMEL_META_INTEGRAL_TYPES_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


///////////////////////////////////////////////////////////////////////////////
//
// Preprocessor Meta-Functions
//

#define CARAMEL_META_INTEGRAL_TYPES_ALL( m ) \
    m( Bool ) m( Int8 ) m( Uint8 ) m( Int16 ) m( Int32 ) m( Uint32 ) m( Int64 ) m( Uint64 )


///////////////////////////////////////////////////////////////////////////////

#endif // __CARAMEL_META_INTEGRAL_TYPES_H
