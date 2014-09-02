// Caramel C++ Library - Metaprogramming Amenity - Range Header

#ifndef __CARAMEL_META_RANGE_H
#define __CARAMEL_META_RANGE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Range of Integer Constants
// - It is a left-closed, right-open range, like STL/Boost iterator ranges.
//
//   NOTES: T and U should be implicitly comparable.
//

template< typename T, T begin, T end >
struct RangeN
{
    static_assert( begin <= end, "begin can't be greater than end" );

    template< typename U >
    static Bool Contains( U value )
    {
        return ( begin <= value ) && ( value < end );
    }
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_META_RANGE_H
