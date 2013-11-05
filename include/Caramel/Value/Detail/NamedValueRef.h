// Caramel C++ Library - Value Amenity - Detail - Named Value Ref Header

#ifndef __CARAMEL_VALUE_NAMED_VALUE_REF_H
#define __CARAMEL_VALUE_NAMED_VALUE_REF_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Constant Named Value
//

class ConstNamedValueRef
{
};


///////////////////////////////////////////////////////////////////////////////
//
// Mutable Named Value
//

class MutableNamedValueRef : public ConstNamedValueRef
{
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_VALUE_NAMED_VALUE_REF_H
