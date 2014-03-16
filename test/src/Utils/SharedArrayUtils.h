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
// Make a Const Shared Array
//

template< typename T >
inline ConstSharedArray< T > MakeConstSharedArray()
{
    return ConstSharedArray< T >();
}


template< typename T >
inline ConstSharedArray< T > MakeConstSharedArray( const T& v0 )
{
    SharedArray< T > ary( 1 );
    ary[0] = v0;
    return ary;
}


template< typename T >
inline ConstSharedArray< T > MakeConstSharedArray( const T& v0, const T& v1 )
{
    SharedArray< T > ary( 2 );
    ary[0] = v0;
    ary[1] = v1;
    return ary;
}


template< typename T >
inline ConstSharedArray< T > MakeConstSharedArray( const T& v0, const T& v1, const T& v2 )
{
    SharedArray< T > ary( 3 );
    ary[0] = v0;
    ary[1] = v1;
    ary[2] = v2;
    return ary;
}


template< typename T >
inline ConstSharedArray< T > MakeConstSharedArray( const T& v0, const T& v1, const T& v2, const T& v3 )
{
    SharedArray< T > ary( 4 );
    ary[0] = v0;
    ary[1] = v1;
    ary[2] = v2;
    ary[3] = v3;
    return ary;
}


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
