// Caramel C++ Library - Value Facility - Named Values Private Header

#ifndef __CARAMEL_VALUE_NAMED_VALUES_IMPL_H
#define __CARAMEL_VALUE_NAMED_VALUES_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include "Value/NamedValueEntry.h"
#include <Caramel/Value/NamedValues.h>
#include <map>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Named Values
//

class NamedValuesImpl
{
public:

    typedef std::map< std::string, NamedValueEntry > ValueMap;


private:

    ValueMap m_values;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_VALUE_NAMED_VALUES_IMPL_H
