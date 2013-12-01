// Caramel C++ Library - String Facility - String Convertible Header

#ifndef __CARAMEL_STRING_STRING_CONVERTIBLE_H
#define __CARAMEL_STRING_STRING_CONVERTIBLE_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Meta/Utility.h>
#include <iosfwd>
#include <type_traits>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// String Convertible
// - Provides an adapter from a custom to std::string.
//

template< typename Derived >
class StringConvertible
{

public:

    /// Stream Operators ////

    friend std::ostream& operator<<( std::ostream& os, const StringConvertible< Derived >& x )
    {
        os << static_cast< const Derived& >( x ).ToString();
        return os;
    }


    //
    // Concept Validation
    // - Check if the Derived has a 'ToString' member function.
    // - Check if Derived::ToString() returns in std::string.
    //

private:

    template< typename T > SizerN< 1 > CheckToString( T );
    SizerN< 2 > CheckToString( const std::string& );

protected:


    ~StringConvertible()
    {
        static_assert(
            sizeof( SizerN< 2 > ) == sizeof( CheckToString( MakeT< const Derived >().ToString() )),
            "The Derived::ToString() doesn't return std::string" );
    }
};


///////////////////////////////////////////////////////////////////////////////
//
// String Convertible Detection
//

template< typename T >
struct IsStringConvertibleT
    : BoolType< std::is_base_of< StringConvertible< T >, T >::value >
{};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_STRING_CONVERTIBLE_H
