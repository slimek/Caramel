// Caramel C++ Library - Configuration Facility - Configuration Root Header

#ifndef __CARAMEL_CONFIGURATION_CONFIG_ROOT_H
#define __CARAMEL_CONFIGURATION_CONFIG_ROOT_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Value/NamedValues.h>
#include <map>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Configuration Root
//

class ConfigRootImpl;

class ConfigRoot
{
public:

    // Read for the default root.
    ConfigRoot();

    // Each section presents as a NamedValues.
    void Load( const std::map< std::string, NamedValues >& sectionMap );

private:

    std::shared_ptr< ConfigRootImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CONFIGURATION_CONFIG_ROOT_H


