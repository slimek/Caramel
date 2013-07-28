// Caramel C++ Library - Numeric Amenity - Number Convertible Header

#ifndef __CARAMEL_NUMERIC_NUMBER_CONVERTIBLE_H
#define __CARAMEL_NUMERIC_NUMBER_CONVERTIBLE_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Meta/Utility.h>
#include <iosfwd>
#include <type_traits>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Number Convertible
// - Provides an adapter from a custom type to an numeric type,
//   including all integral and floating types.
//

struct NumberConvertibleTag {};

template< typename Derived, typename NumberType >
class NumberConvertible : public NumberConvertibleTag
{
    static_assert(
        std::is_arithmetic< NumberType >::value,
        "Must represents as an integral or floating-point type" );

public:

    typedef NumberType NumberType;

    /// Stream Operators ///

    friend std::ostream& operator<<(
        std::ostream& os, const NumberConvertible< Derived, NumberType >& x )
    {
        os << static_cast< const Derived& >( x ).ToNumber();
        return os;
    }


    //
    // Concept Validation
    // - Check if the Derived has a 'ToNumber' member function.
    // - Check if Derived::ToNumber() returns in NumberType.
    //

private:

    template< typename T > SizerN< 1 > CheckToInteger( T );
    SizerN< 2 > CheckToInteger( NumberType );

protected:

    ~NumberConvertible()
    {
        static_assert(
            sizeof( SizerN< 2 > ) == sizeof( CheckToInteger( MakeT< const Derived >().ToNumber() )),
            "The Derived::ToNumber() doesn't return NumberType exactly" );
    }
};


///////////////////////////////////////////////////////////////////////////////
//
// Integer Convertible Detection
//

template< typename T >
struct IsNumberConvertibleT
    : BoolType< std::is_base_of< NumberConvertibleTag, T >::value >
{};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_NUMERIC_NUMBER_CONVERTIBLE_H
