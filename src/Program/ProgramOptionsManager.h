// Caramel C++ Library - Program Facility - Program Options Manager Header

#ifndef __CARAMEL_PROGRAM_PROGRAM_OPTIONS_MANAGER_H
#define __CARAMEL_PROGRAM_PROGRAM_OPTIONS_MANAGER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Object/FacilityLongevity.h"
#include <Caramel/Object/Singleton.h>
#include <Caramel/Program/ProgramOptions.h>
#include <boost/program_options.hpp>
#include <vector>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Program Options Manager
//

class ProgramOptionsManager
    : public Singleton< ProgramOptionsManager, FACILITY_LONGEVITY_PROGRAM_OPTIONS >
{
public:

    ProgramOptionsManager();

    /// Add Options ///

    void AddBoolOption( const std::string& name );

    void AddStringOption( const std::string& name );
    void AddStringOptionWithDefault( const std::string& name, const std::string& defaultValue );

    void AddPositionalOptions( const std::vector< ProgramOptionValue >& options );


    /// Parsing ///

    void ParseArguments( const std::vector< std::string >& arguments );
    void ParseCommandLine();


    /// Find and Get Options ///

    Bool Contains( const std::string& longName ) const;

    std::string GetStringOption( const std::string& longName ) const;


private:

    std::vector< std::string > m_arguments;

    boost::program_options::options_description m_optionsDesc;
    boost::program_options::variables_map       m_variablesMap;

    Bool m_positionalAdded;
    boost::program_options::positional_options_description m_positionalDesc;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_PROGRAM_PROGRAM_OPTIONS_MANAGER_H
