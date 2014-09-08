// Caramel C++ Library - Configuration Facility - Configuration Section Private Header

#ifndef __CARAMEL_CONFIGURATION_CONFIG_SECTION_IMPL_H
#define __CARAMEL_CONFIGURATION_CONFIG_SECTION_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Concurrent/Map.h>
#include <Caramel/Configuration/ConfigSection.h>
#include <Caramel/Value/NamedValues.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Configuration Section
//

class ConfigSectionImpl
{
public:

    explicit ConfigSectionImpl( const std::string& name );


    std::string GetName() const { return m_name; }


    void AddValue( ConfigValue* value );

    void Load( const NamedValues& values );


private:

    std::string m_name;

    typedef Concurrent::MapWithSnapshot< std::string, ConfigValue* > ValueMap;
    ValueMap m_values;

};

typedef std::shared_ptr< ConfigSectionImpl > ConfigSectionPtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CONFIGURATION_CONFIG_SECTION_IMPL_H
