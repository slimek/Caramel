// Caramel C++ Library - Configuration Facility - Configuration Section Header

#ifndef __CARAMEL_CONFIGURATION_CONFIG_SECTION_H
#define __CARAMEL_CONFIGURATION_CONFIG_SECTION_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Configuration Section
//

class ConfigSectionImpl;
class ConfigValue;

class ConfigSection
{
public:

    explicit ConfigSection( const std::string& name );


    void AddValue( ConfigValue& value );


private:

    std::shared_ptr< ConfigSectionImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CONFIGURATION_CONFIG_SECTION_H
