// Caramel C++ Library - Numeric Amenity - Number Traits Header

#ifndef __CARAMEL_NUMERIC_NUMBER_TRAITS_H
#define __CARAMEL_NUMERIC_NUMBER_TRAITS_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Meta/IfThenElse.h>
#include <type_traits>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Number Traits Adapters
//

template< typename T >
struct NumberTraits_Arithmetic
{
    typedef T NumberType;
};


template< typename T >
struct NumberTraits_Enum
{
    typedef typename std::underlying_type< T >::type NumberType;
};


///////////////////////////////////////////////////////////////////////////////
//
// Number Traits Select
//

template< typename T >
struct NumberTraitsSelect
{
    typedef typename IfThenElse2T
    <
        std::is_arithmetic< T >::value, NumberTraits_Arithmetic< T >,
        std::is_enum< T >::value,       NumberTraits_Enum< T >,
                                        EmptyType
    >::Type TraitsType;
};


} // namespace Detail

///////////////////////////////////////////////////////////////////////////////
//
// Number Traits
//

/// Primary Template ///

template< typename T >
struct NumberTraits
    : public Detail::NumberTraitsSelect< T >::TraitsType
{};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_NUMERIC_NUMBER_TRAITS_H
