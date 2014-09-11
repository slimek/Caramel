// Caramel C++ Library - Configuration Facility - Configuration Root Private Header

#ifndef __CARAMEL_CONFIGURATION_CONFIG_ROOT_IMPL_H
#define __CARAMEL_CONFIGURATION_CONFIG_ROOT_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Configuration/ConfigSectionImpl.h"
#include <Caramel/Concurrent/Map.h>
#include <Caramel/Configuration/ConfigRoot.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Configuration Root
//

class ConfigRootImpl
{
public:

    explicit ConfigRootImpl( const std::string& name );

    void AddSection( ConfigSectionPtr section );

    void Load( const std::map< std::string, NamedValues >& sectionMap );

    std::string GetName() const { return m_name; }

private:

    std::string m_name;

    typedef Concurrent::MapWithSnapshot< std::string, ConfigSectionPtr > SectionMap;
    SectionMap m_sections;
};

typedef std::shared_ptr< ConfigRootImpl > ConfigRootPtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CONFIGURATION_CONFIG_ROOT_IMPL_H
