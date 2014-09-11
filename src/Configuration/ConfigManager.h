// Caramel C++ Library - Configuration Facility - Configuration Manager Header

#ifndef __CARAMEL_CONFIGURATION_CONFIG_MANAGER_H
#define __CARAMEL_CONFIGURATION_CONFIG_MANAGER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Configuration/ConfigRootImpl.h"
#include <Caramel/Object/Singleton.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Configuration Manager
//

class ConfigManager : public Singleton< ConfigManager >
{
public:

    ConfigRootPtr FindOrCreateRoot( const std::string& name );

private:

    typedef Concurrent::Map< std::string, ConfigRootPtr > RootMap;
    RootMap m_roots;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CONFIGURATION_CONFIG_MANAGER_H
