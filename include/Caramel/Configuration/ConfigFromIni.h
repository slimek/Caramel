// Caramel C++ Library - Configuration Facility - Configuration From INI Header

#ifndef __CARAMEL_CONFIGURATION_CONFIG_FROM_INI_H
#define __CARAMEL_CONFIGURATION_CONFIG_FROM_INI_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Document/IniDocument.h>
#include <Caramel/Value/NamedValues.h>
#include <map>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Convert an IniDocument into a map of NamedValues.
// Each NamedValues presents an IniSection.
//

inline std::map< std::string, NamedValues > MakeConfigSectionMap( const IniDocument& ini )
{
    std::map< std::string, NamedValues > sectionMap;

    for ( auto section : ini.GetAllSections() )
    {
        sectionMap.insert( std::make_pair( section.GetName(), section.ToNamedValues() ));
    }

    return sectionMap;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CONFIGURATION_CONFIG_FROM_INI_H
