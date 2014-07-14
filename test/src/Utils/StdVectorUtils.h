// Caramel C++ Library Test - Utilits - std::vector Utilities Header

#ifndef __CARAMEL_TEST_UTILS_STD_VECTOR_UTILS_H
#define __CARAMEL_TEST_UTILS_STD_VECTOR_UTILS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Random/UniformRandom.h>
#include <vector>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Make a random std::vector< Int >
//

inline std::vector< Int > MakeRandomVector( Uint size, Int minValue, Int maxValue )
{
    std::vector< Int > vec( size );

    for ( Uint i = 0; i < size; ++ i )
    {
        vec[i] = GenRandomInt( minValue, maxValue );
    }

    return vec;
}


///////////////////////////////////////////////////////////////////////////////
//
// Test the content of a vector is sorted.
//

template< typename T >
inline Bool IsSorted( const std::vector< T >& vec )
{
    if ( vec.size() < 2 ) { return true; }

    for ( Uint i = 0; i < vec.size() - 1; ++ i )
    {
        if ( vec[i] > vec[i+1] ) { return false; }
    }

    return true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TEST_UTILS_STD_VECTOR_UTILS_H
