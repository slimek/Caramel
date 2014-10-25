// Caramel C++ Library - Numeric Amenity - Number Relation Header

#ifndef __CARAMEL_NUMERIC_NUMBER_RELATION_H
#define __CARAMEL_NUMERIC_NUMBER_RELATION_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Meta/IfThenElse.h>
#include <Caramel/Numeric/Detail/NumberRelationArithmetic.h>
#include <Caramel/Numeric/Detail/NumberRelationEnum.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Number Relation Select
//

template< typename OutputT, typename InputT >
struct NumberRelationSelect
{
    typedef typename IfThenElse2T
    <
        std::is_fundamental< InputT >::value,   NumberRelation_Arithmetic< OutputT, InputT >,
        std::is_enum< InputT >::value,          NumberRelation_Enum< OutputT, InputT >,
                                                EmptyType
    >::Type RelationType;
};


} // namespace Detail


///////////////////////////////////////////////////////////////////////////////
//
// Number Relation
// - A traits of the relation between two numeric type, one for input and
//   one for output.
//

template< typename OutputT, typename InputT >
struct NumberRelation
    : Detail::NumberRelationSelect< OutputT, InputT >::RelationType
{};


// Specialized relation of type itself
template< typename T >
struct NumberRelation< T, T >
{
    static Bool CanExactConvert( T ) { return true; }
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_NUMERIC_NUMBER_RELATION_H
