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


//
// Specialization for Floating Types
//

template<>
struct NumberTraits< Float >
    : public Detail::NumberTraits_Arithmetic< Float >
{
    //
    // Exact Integer Limits
    // - You may convert these integers to Double without losing precision.
    //
    
    static const Int32  MAX_EXACT_INT32  = 0xFFFFFF;  // 24 bits
    static const Int32  MIN_EXACT_INT32  = - MAX_EXACT_INT32;
    static const Uint32 MAX_EXACT_UINT32 = MAX_EXACT_INT32;


    //
    // Conversion Traits
    //

    template< typename T >
    static Bool CanExactConvert( T value )
    {
        static_assert( std::is_integral< T >::value, "T must be integral type" );
        return true;
    }

    template<>
    static Bool CanExactConvert< Int64 >( Int64 value )
    {
        return MIN_EXACT_INT32 <= value && value <= MAX_EXACT_INT32;
    }

    template<>
    static Bool CanExactConvert< Uint64 >( Uint64 value )
    {
        return value <= MAX_EXACT_UINT32;
    }
};


template<>
struct NumberTraits< Double >
    : public Detail::NumberTraits_Arithmetic< Double >
{
    //
    // Exact Integer Limits
    // - You may convert these integers to Double without losing precision.
    //
    
    static const Int64  MAX_EXACT_INT64  = 0x1FFFFFFFFFFFFFll;  // 53 bits
    static const Int64  MIN_EXACT_INT64  = - MAX_EXACT_INT64;
    static const Uint64 MAX_EXACT_UINT64 = MAX_EXACT_INT64;


    //
    // Conversion Traits
    //

    template< typename T >
    static Bool CanExactConvert( T value )
    {
        static_assert( std::is_integral< T >::value, "T must be integral type" );
        return true;
    }

    template<>
    static Bool CanExactConvert< Int64 >( Int64 value )
    {
        return MIN_EXACT_INT64 <= value && value <= MAX_EXACT_INT64;
    }

    template<>
    static Bool CanExactConvert< Uint64 >( Uint64 value )
    {
        return value <= MAX_EXACT_UINT64;
    }
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_NUMERIC_NUMBER_TRAITS_H
