// Caramel C++ Library - Numeric Amenity - Number Converter Header

#ifndef __CARAMEL_NUMERIC_NUMBER_CONVERTER_H
#define __CARAMEL_NUMERIC_NUMBER_CONVERTER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Numeric/NumberRelation.h>
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
struct NumberConverter : public NumberRelation< OutputT, InputT >
{
    using NumberRelation< OutputT, InputT >::CanExactConvert;

    static Bool TryExactConvert( OutputT& outValue, InputT inValue )
    {
        if ( ! CanExactConvert( inValue )) { return false; }

        outValue = static_cast< OutputT >( inValue );
        return true;
    }
};


// A type can always exactly convert to itself
template< typename T >
struct NumberConverter< T, T > : public NumberRelation< T, T >
{
    static Bool TryExactConvert( T& outValue, T inValue )
    {
        outValue = inValue;
        return true;
    }
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_NUMERIC_NUMBER_CONVERTER_H
