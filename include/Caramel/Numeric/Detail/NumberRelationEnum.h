// Caramel C++ Library - Numeric Amenity - Number Relation of Enum Header

#ifndef __CARAMEL_NUMERIC_DETAIL_NUMBER_RELATION_ENUM_H
#define __CARAMEL_NUMERIC_DETAIL_NUMBER_RELATION_ENUM_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Numeric/Detail/NumberRelationArithmetic.h>
#include <type_traits>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Number Relation of Enum
// - Specialized when the input type is an enum.
//
//   Bypass all functions to the relation of the enum's underline type.
//

template< typename OutputT, typename InputT >
struct NumberRelation_Enum
{
    static_assert( std::is_enum< InputT >::value, "Input type should be an enum" );

    static Bool CanExactConvert( InputT value )
    {
        typedef typename std::underlying_type< InputT >::type UnderlineType;

        return NumberRelation_Arithmetic< OutputT, UnderlineType >::CanExactConvert( value );
    }
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_NUMERIC_DETAIL_NUMBER_RELATION_ENUM_H
