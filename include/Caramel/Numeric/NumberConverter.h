// Caramel C++ Library - Numeric Amenity - Number Converter Header

#ifndef __CARAMEL_NUMERIC_NUMBER_CONVERTER_H
#define __CARAMEL_NUMERIC_NUMBER_CONVERTER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Numeric/NumberTraits.h>
#include <cfloat>


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

    static Bool TryExactConvert( Int32& outValue, Int64 inValue )
    {
        if ( ! CanExactConvert( inValue )) { return false; }

        outValue = static_cast< Int32 >( inValue );
        return true;
    }
};


template<>
struct NumberConverter< Int32, Uint64 >
{
    static Bool CanExactConvert( Uint64 value )
    {
        return value <= INT32_MAX;
    }

    static Bool TryExactConvert( Int32& outValue, Uint64 inValue )
    {
        if ( ! CanExactConvert( inValue )) { return false; }

        outValue = static_cast< Int32 >( inValue );
        return true;
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

    static Bool TryExactConvert( Uint32& outValue, Int64 inValue )
    {
        if ( ! CanExactConvert( inValue )) { return false; }

        outValue = static_cast< Uint32 >( inValue );
        return true;
    }
};


template<>
struct NumberConverter< Uint32, Uint64 >
{
    static Bool CanExactConvert( Uint64 value )
    {
        return value <= UINT32_MAX;
    }

    static Bool TryExactConvert( Uint32& outValue, Uint64 inValue )
    {
        if ( ! CanExactConvert( inValue )) { return false; }

        outValue = static_cast< Uint32 >( inValue );
        return true;
    }
};


//
// Specialization - Output to Int64
//

template<>
struct NumberConverter< Int64, Uint64 >
{
    static Bool CanExactConvert( Uint64 value )
    {
        return value <= INT64_MAX;
    }

    static Bool TryExactConvert( Int64& outValue, Uint64 inValue )
    {
        if ( ! CanExactConvert( inValue )) { return false; }

        outValue = static_cast< Int64 >( inValue );
        return true;
    }
};


//
// Specialization - Output to Uint64
//

template<>
struct NumberConverter< Uint64, Int64 >
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

template<>
struct NumberConverter< Float, Double >
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
