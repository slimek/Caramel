// Caramel C++ Library Test - Utilits - std::vector Utilities Header

#ifndef __CARAMEL_TEST_UTILS_STD_VECTOR_UTILS_H
#define __CARAMEL_TEST_UTILS_STD_VECTOR_UTILS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Random/UniformRandom.h>
#include <algorithm>
#include <set>
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
//
// Compare a vector with a set of data,
// returns true if each element matched just once.
//

template< typename T >
inline Bool ExactlyMatch( const std::vector< T >& v, std::initializer_list< T >&& init )
{
    std::set< T > s( std::move( init ));

    for ( const auto& x : v )
    {
        auto iter = s.find( x );
        if ( iter == s.end() ) { return false; }
        s.erase( iter );
    }

    return s.empty();
}


///////////////////////////////////////////////////////////////////////////////
//
// Sort a vector by the element's member function, or member extractor.
//

template< typename T, typename Getter >
inline void SortBy( std::vector< T >& v, Getter getter )
{
    std::sort( v.begin(), v.end(),
    [&] ( const T& lhs, const T& rhs )
    {
        return getter( lhs ) < getter( rhs );
    });
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TEST_UTILS_STD_VECTOR_UTILS_H
