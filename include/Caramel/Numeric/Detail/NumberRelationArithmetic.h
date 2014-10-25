// Caramel C++ Library - Numeric Amenity - Detail - Number Relation of Arithmetic Header

#ifndef __CARAMEL_NUMERIC_DETAIL_NUMBER_RELATION_ARITHMETIC_H
#define __CARAMEL_NUMERIC_DETAIL_NUMBER_RELATION_ARITHMETIC_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Numeric/NumberTraits.h>
#include <cstdint>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Number Relation of Arithmetic
// - A traits of the relation between two arithmetic types, one for input and
//   one for output.
//

// Primary Template
template< typename OutputT, typename InputT >
struct NumberRelation_Arithmetic;


// A type can always exactly convert to itself
template< typename T >
struct NumberRelation_Arithmetic< T, T >
{
    static Bool CanExactConvert( T value ) { return true; }
};


//
// Specialization - Output to Int32
//

template<>
struct NumberRelation_Arithmetic< Int32, Int64 >
{
    static Bool CanExactConvert( Int64 value )
    {
        return INT32_MIN <= value && value <= INT32_MAX;
    }
};


template<>
struct NumberRelation_Arithmetic< Int32, Uint64 >
{
    static Bool CanExactConvert( Uint64 value )
    {
        return value <= INT32_MAX;
    }
};


//
// Specialization - Output to Uint32
//

template<>
struct NumberRelation_Arithmetic< Uint32, Int32 >
{
    static Bool CanExactConvert( Int32 value )
    {
        return 0 <= value;
    }
};


template<>
struct NumberRelation_Arithmetic< Uint32, Int64 >
{
    static Bool CanExactConvert( Int64 value )
    {
        return 0 <= value && value <= UINT32_MAX;
    }
};


template<>
struct NumberRelation_Arithmetic< Uint32, Uint64 >
{
    static Bool CanExactConvert( Uint64 value )
    {
        return value <= UINT32_MAX;
    }

};


//
// Specialization - Output to Int64
//

template<>
struct NumberRelation_Arithmetic< Int64, Uint64 >
{
    static Bool CanExactConvert( Uint64 value )
    {
        return value <= INT64_MAX;
    }
};


//
// Specialization - Output to Uint64
//

template<>
struct NumberRelation_Arithmetic< Uint64, Int64 >
{
    static Bool CanExactConvert( Int64 value )
    {
        return 0 <= value;
    }
};


//
// Specialization - Output to Float
//

template<>
struct NumberRelation_Arithmetic< Float, Int32 >
{
    static Bool CanExactConvert( Int32 value )
    {
        return FloatTraits::MIN_EXACT_INT32 <= value && value <= FloatTraits::MAX_EXACT_INT32;
    }
};

template<>
struct NumberRelation_Arithmetic< Float, Uint32 >
{
    static Bool CanExactConvert( Uint32 value )
    {
        return value <= FloatTraits::MAX_EXACT_UINT32;
    }
};

template<>
struct NumberRelation_Arithmetic< Float, Int64 >
{
    static Bool CanExactConvert( Int64 value )
    {
        return FloatTraits::MIN_EXACT_INT32 <= value && value <= FloatTraits::MAX_EXACT_INT32;
    }
};

template<>
struct NumberRelation_Arithmetic< Float, Uint64 >
{
    static Bool CanExactConvert( Uint64 value )
    {
        return value <= FloatTraits::MAX_EXACT_UINT32;
    }
};

template<>
struct NumberRelation_Arithmetic< Float, Double >
{
    static Bool CanExactConvert( Double value )
    {
        return -FLT_MAX <= value && value <= FLT_MAX;
    }
};


//
// Specialization - Output to Double
//

template<>
struct NumberRelation_Arithmetic< Double, Int32 >
{
    static Bool CanExactConvert( Int32 value ) { return true; }
};


template<>
struct NumberRelation_Arithmetic< Double, Uint32 >
{
    static Bool CanExactConvert( Uint32 value ) { return true; }
};


template<>
struct NumberRelation_Arithmetic< Double, Int64 >
{
    static Bool CanExactConvert( Int64 value )
    {
        return DoubleTraits::MIN_EXACT_INT64 <= value && value <= DoubleTraits::MAX_EXACT_INT64;
    }
};

template<>
struct NumberRelation_Arithmetic< Double, Uint64 >
{
    static Bool CanExactConvert( Uint64 value )
    {
        return value <= DoubleTraits::MAX_EXACT_UINT64;
    }
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_NUMERIC_DETAIL_NUMBER_RELATION_ARITHMETIC_H
