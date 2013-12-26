// Caramel C++ Library - Memory Amenity - Shared Ptr Utilities Header

#ifndef __CARAMEL_MEMORY_SHARED_PTR_UTILS_H
#define __CARAMEL_MEMORY_SHARED_PTR_UTILS_H
#pragma once

#include <Caramel/Caramel.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Arithmetic
// - Helper functions for arithmetic of contained objects.
//   Based on copy-on-write policy.
//

template< typename T, typename U >
inline void AddAssign( std::shared_ptr< T >& lhs, const std::shared_ptr< U >& rhs )
{
    if ( lhs.unique() )
    {
        *lhs += *rhs;
    }
    else
    {
        auto copy = std::make_shared< T >( *lhs );
        *copy += *rhs;
        lhs = copy;
    }
}


template< typename T, typename U >
inline void SubstractAssign( std::shared_ptr< T >& lhs, const std::shared_ptr< U >& rhs )
{
    if ( lhs.unique() )
    {
        *lhs -= *rhs;
    }
    else
    {
        auto copy = std::make_shared< T >( *lhs );
        *copy -= *rhs;
        lhs = copy;
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_MEMORY_SHARED_PTR_UTILS_H
