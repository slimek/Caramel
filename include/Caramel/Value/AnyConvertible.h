// Caramel C++ Library - Value Facility - Any Convertible Header

#ifndef __CARAMEL_VALUE_ANY_CONVERTIBLE_H
#define __CARAMEL_VALUE_ANY_CONVERTIBLE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Meta/Utility.h>


namespace Caramel
{

// Forwards declaration
class Any;

///////////////////////////////////////////////////////////////////////////////
//
// Any Convertible
// - Provides an adapter from a custom type to an Any.
//
//   You may use this to control how a type is stored in Any.
//   For example, some string-like types may want to just be a string
//   when they are passed to an Any.
//

struct AnyConvertibleTag {};

template< typename Derived >
class AnyConvertible : public AnyConvertibleTag
{
    //
    // Concept Validation
    // - Check if the Derived has a 'ToAny' member function.
    // - Check if Derived::ToAny() returns in Any.
    //

private:

    template< typename T > SizerN< 1 > CheckToAny( T );
    SizerN< 2 > CheckToAny( const Any& );

protected:

    ~AnyConvertible()
    {
        static_assert(
            sizeof( SizerN< 2 > ) == sizeof( CheckToAny( MakeT< const Derived >().ToAny() )),
            "The Derived::ToAny() doesn't return Any" );
    }
};


///////////////////////////////////////////////////////////////////////////////
//
// Any Convertible Detection
//

template< typename T >
struct IsAnyConvertibleT
    : BoolType< std::is_base_of< AnyConvertibleTag, T >::value >
{};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_VALUE_ANY_CONVERTIBLE_H
