// Caramel C++ Library - Memory Amenity - std::shared_ptr Utilities Header

#ifndef __CARAMEL_MEMORY_SHARED_PTR_UTILS_H
#define __CARAMEL_MEMORY_SHARED_PTR_UTILS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <boost/smart_ptr/detail/spinlock_pool.hpp>


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
//
// Atomic Operation
// - Android NDK r9 doesn't support C++11 atomic for std::shared_ptr.
//   You may use std::atomic_load() and atomic_store() if you have NDK r10 or later.
//

template< typename T >
inline std::shared_ptr< T > AtomicLoad( const std::shared_ptr< T >* sp )
{
    boost::detail::spinlock::scoped_lock lock(
        boost::detail::spinlock_pool< 0 >::spinlock_for( &sp ));
    std::shared_ptr< T > result = *sp;
    return result;
}


template< typename T >
inline void AtomicStore( std::shared_ptr< T >* sp, std::shared_ptr< T > other )
{
    boost::detail::spinlock::scoped_lock lock(
        boost::detail::spinlock_pool< 0 >::spinlock_for( &sp ));
    sp->swap( other );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_MEMORY_SHARED_PTR_UTILS_H
