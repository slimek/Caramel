// Caramel C++ Library Test - Utilits - Matcher Header

#ifndef __CARAMEL_TEST_UTILS_MATCHER_H
#define __CARAMEL_TEST_UTILS_MATCHER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <boost/operators.hpp>
#include <set>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Matcher
// - Match a set of value with a container,
//   Returns true if each element matched just once.
//

template< typename T >
class Matcher
{
public:
    Matcher( std::initializer_list< T >&& init );

    template< typename Container >
    Bool Match( const Container& c ) const;

private:

    std::initializer_list< T > m_init;
};


//
// Helper Function
//

template< typename T, typename Container >
inline Bool Match( const Container& c, std::initializer_list< T >&& init )
{
    Matcher< T > ma( std::move( init ));
    return ma.Match( c );
}


//
// Implementation
//

template< typename T >
inline Matcher< T >::Matcher( std::initializer_list< T >&& init )
    : m_init( std::move( init ))
{
}


template< typename T >
template< typename Container >
inline Bool Matcher< T >::Match( const Container& c ) const
{
    std::set< T > s( m_init );

    for ( const auto& x : c )
    {
        auto iter = s.find( x );
        if ( iter == s.end() ) { return false; }
        s.erase( iter );
    }

    return s.empty();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_TEST_UTILS_MATCHER_H

