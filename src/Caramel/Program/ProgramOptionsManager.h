// Caramel C++ Library - Program Facility - Program Options Manager Header

#ifndef __CARAMEL_PROGRAM_PROGRAM_OPTIONS_MANAGER_H
#define __CARAMEL_PROGRAM_PROGRAM_OPTIONS_MANAGER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Object/Singleton.h>
#include <boost/program_options.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Program Options Manager
//

class ProgramOptionsManager : public Singleton< ProgramOptionsManager >
{
public:

    /// Add Options ///

    void AddBoolOption( const std::string& name );

    void AddStringOption( const std::string& name );
    void AddStringOptionWithDefault( const std::string& name, const std::string& defaultValue );


    /// Parsing ///

    void ParseCommandLine();


    /// Find and Get Options ///

    Bool Contains( const std::string& longName ) const;

    std::string GetStringOption( const std::string& longName ) const;


private:

    boost::program_options::options_description m_optionsDesc;
    boost::program_options::variables_map       m_variablesMap;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_PROGRAM_PROGRAM_OPTIONS_MANAGER_H
