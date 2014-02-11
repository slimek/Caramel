// Caramel C++ Library - Memory Amenity - Unique Ptr Utilities Header

#ifndef __CARAMEL_MEMORY_UNIQUE_PTR_UTILS_H
#define __CARAMEL_MEMORY_UNIQUE_PTR_UTILS_H
#pragma once

#include <Caramel/Caramel.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Make Unique
// - TODO: Replace this function when std::make_unique() (since C++14) is available.
//

template< typename T >
inline std::unique_ptr< T > MakeUnique()
{
    return std::unique_ptr< T >( new T );
}


template< typename T, typename A1 >
inline std::unique_ptr< T > MakeUnique( A1&& a1 )
{
    return std::unique_ptr< T >( new T( std::forward< A1 >( a1 )));
}


template< typename T, typename A1, typename A2 >
inline std::unique_ptr< T > MakeUnique( A1&& a1, A2&& a2 )
{
    return std::unique_ptr< T >( new T( std::forward< A1 >( a1 ), std::forward< A2 >( a2 )));
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_MEMORY_UNIQUE_PTR_UTILS_H
