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


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_NUMERIC_DETAIL_NUMBER_RELATION_ARITHMETIC_H
