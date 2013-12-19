// Caramel C++ Library - Numeric Amenity - Number Converter Header

#ifndef __CARAMEL_NUMERIC_NUMBER_CONVERTER_H
#define __CARAMEL_NUMERIC_NUMBER_CONVERTER_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Numeric/NumberTraits.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Number Converter
// - Converters between arithmetic types.
//

// Primary Template
template< typename OutputT, typename InputT >
struct NumberConverter;


//
// Specialization - Output to Int32
//

template<>
struct NumberConverter< Int32, Int64 >
{
    static Bool CanExactConvert( Int64 value )
    {
        return INT32_MIN <= value && value <= INT32_MAX;
    }
};


template<>
struct NumberConverter< Int32, Uint64 >
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
struct NumberConverter< Uint32, Int64 >
{
    static Bool CanExactConvert( Int64 value )
    {
        return 0 <= value && value <= UINT32_MAX;
    }
};


template<>
struct NumberConverter< Uint32, Uint64 >
{
    static Bool CanExactConvert( Uint64 value )
    {
        return value <= UINT32_MAX;
    }
};


//
// Specialization - Output to Float
//

template<>
struct NumberConverter< Float, Int32 >
{
    static Bool CanExactConvert( Int32 value )
    {
        return FloatTraits::MIN_EXACT_INT32 <= value && value <= FloatTraits::MAX_EXACT_INT32;
    }
};

template<>
struct NumberConverter< Float, Uint32 >
{
    static Bool CanExactConvert( Uint32 value )
    {
        return value <= FloatTraits::MAX_EXACT_UINT32;
    }
};

template<>
struct NumberConverter< Float, Int64 >
{
    static Bool CanExactConvert( Int64 value )
    {
        return FloatTraits::MIN_EXACT_INT32 <= value && value <= FloatTraits::MAX_EXACT_INT32;
    }
};

template<>
struct NumberConverter< Float, Uint64 >
{
    static Bool CanExactConvert( Uint64 value )
    {
        return value <= FloatTraits::MAX_EXACT_UINT32;
    }
};


//
// Specialization - Output to Double
//

template<>
struct NumberConverter< Double, Int32 >
{
    static Bool CanExactConvert( Int32 value ) { return true; }
};

template<>
struct NumberConverter< Double, Uint32 >
{
    static Bool CanExactConvert( Uint32 value ) { return true; }
};

template<>
struct NumberConverter< Double, Int64 >
{
    static Bool CanExactConvert( Int64 value )
    {
        return DoubleTraits::MIN_EXACT_INT64 <= value && value <= DoubleTraits::MAX_EXACT_INT64;
    }
};

template<>
struct NumberConverter< Double, Uint64 >
{
    static Bool CanExactConvert( Uint64 value )
    {
        return value <= DoubleTraits::MAX_EXACT_UINT64;
    }
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_NUMERIC_NUMBER_CONVERTER_H
