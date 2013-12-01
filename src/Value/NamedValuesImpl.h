// Caramel C++ Library - Value Facility - Named Values Private Header

#ifndef __CARAMEL_VALUE_NAMED_VALUES_IMPL_H
#define __CARAMEL_VALUE_NAMED_VALUES_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
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
    friend class NamedValues;

public:

    Detail::NamedValueEntry* InsertValue( const std::string& name );

private:

    typedef std::map< std::string, Detail::NamedValueEntry > ValueMap;
    ValueMap m_valueEntries;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_VALUE_NAMED_VALUES_IMPL_H
