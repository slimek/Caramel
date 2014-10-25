// Caramel C++ Library - Value Facility - Named Values Private Header

#ifndef __CARAMEL_VALUE_NAMED_VALUES_IMPL_H
#define __CARAMEL_VALUE_NAMED_VALUES_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Value/NamedValues.h>
#include <Caramel/Value/Scalar.h>
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

    Scalar* InsertValue( const std::string& name );

private:

    typedef std::map< std::string, Scalar > ValueMap;
    ValueMap m_values;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_VALUE_NAMED_VALUES_IMPL_H
