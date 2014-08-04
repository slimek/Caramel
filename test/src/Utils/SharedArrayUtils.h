// Caramel C++ Library Test - Utilits - SharedArray Utilities Header

#ifndef __CARAMEL_TEST_UTILS_SHARED_ARRAY_UTILS_H
#define __CARAMEL_TEST_UTILS_SHARED_ARRAY_UTILS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Value/SharedArray.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Compare if two Shared Array are equal.
//

template< typename T, typename U >
inline Bool operator==( const ConstSharedArray< T >& lhs, const ConstSharedArray< U >& rhs )
{
    if ( lhs.Size() != rhs.Size() ) { return false; }

    for ( Uint i = 0; i < lhs.Size(); ++ i )
    {
        if ( lhs[i] != rhs[i] ) { return false; }
    }

    return true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TEST_UTILS_SHARED_ARRAY_UTILS_H
