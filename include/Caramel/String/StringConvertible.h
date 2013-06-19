// Caramel C++ Library - String Facility - String Convertible Header

#ifndef __CARAMEL_STRING_STRING_CONVERTIBLE_H
#define __CARAMEL_STRING_STRING_CONVERTIBLE_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Meta/Select.h>
#include <Caramel/Meta/Utility.h>
#include <iosfwd>
#include <type_traits>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// String Convertible
// - Provides an interface to std::string from a custom type.
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

    SizerN< 1 > CheckToString( ... );
    SizerN< 1 > CheckToString( const Char* );
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
    : SelectT
    <
        std::is_class< T >::value,
        BoolType< std::is_base_of< StringConvertible< T >, T >::value >,
        FalseType
    >::Type
{};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_STRING_CONVERTIBLE_H
