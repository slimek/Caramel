// Caramel C++ Library - Program Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Error/CatchException.h>
#include <Caramel/Program/ConsoleApplication.h>
#include <Caramel/Program/ProgramOptions.h>
#include <Caramel/Program/ProgramOptionsManager.h>
#include <Caramel/String/Algorithm.h>
#include <functional>
#include <iostream>


namespace Caramel
{

//
// Contents
//
// < Application >
//   ConsoleApplication
// 
// < Program Options >
//   ProgramOptionsManager
//   ProgramOption
//   ProgramOptionBool
//   ProgramOptionString
//

///////////////////////////////////////////////////////////////////////////////
//
// Console Application
//

Int ConsoleApplication::Run()
{
    auto xc = CatchException( [ this ] { return this->Main(); } );
    if ( xc )
    {
        std::cout << std::endl
                  << "Program caught an exception and exit abnormally." << std::endl;
        std::cin.get();
    }
    return xc.Result();
}


///////////////////////////////////////////////////////////////////////////////
//
// Program Options Manager
//

//
// Add Options
//

void ProgramOptionsManager::AddBoolOption( const std::string& name )
{
    m_optionsDesc.add_options()( name.c_str(), "" );
    
    // NOTE: ignore the second parameter "description" with an empty string.
}


void ProgramOptionsManager::AddStringOption( const std::string& name )
{
    m_optionsDesc.add_options()(
        name.c_str(),
        boost::program_options::value< std::string >()
    );
}


void ProgramOptionsManager::AddStringOptionWithDefault(
    const std::string& name, const std::string& defaultValue )
{
    m_optionsDesc.add_options()(
        name.c_str(),
        boost::program_options::value< std::string >()->default_value( defaultValue )
    );
}


//
// Parsing
//

void ProgramOptionsManager::ParseCommandLine()
{
    namespace po = boost::program_options;

    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    {
        po::store(
            po::command_line_parser( po::split_winmain( ::GetCommandLineA() ))
                .options( m_optionsDesc )
                .allow_unregistered()
                .run(),
            m_variablesMap
        );

        po::notify( m_variablesMap );
    }
    #else
    {
        CARAMEl_NOT_IMPLEMETNED();
    }
    #endif
}


//
// Find and Get Options
//

Bool ProgramOptionsManager::Contains( const std::string& longName ) const
{
    return 0 != m_variablesMap.count( longName );
}


std::string ProgramOptionsManager::GetStringOption( const std::string& longName ) const
{
    if ( ! this->Contains( longName ))
    {
        CARAMEL_THROW( "Option not found, longName: %s", longName );
    }

    return m_variablesMap[ longName ].as< std::string >();
}


///////////////////////////////////////////////////////////////////////////////
//
// Program Option
//

ProgramOption::ProgramOption( const std::string& name )
{
    m_longName = Contains( name, ',' )
               ? BeforeFirst( name, ',' )
               : name;
}


Bool ProgramOption::Exists() const
{
    return ProgramOptionsManager::Instance()->Contains( m_longName );
}


void ProgramOption::ParseCommandLine()
{
    ProgramOptionsManager::Instance()->ParseCommandLine();
}


///////////////////////////////////////////////////////////////////////////////
//
// Program Option Bool
//

ProgramOptionBool::ProgramOptionBool( const std::string& name )
    : ProgramOption( name )
{
    ProgramOptionsManager::Instance()->AddBoolOption( name );
}


///////////////////////////////////////////////////////////////////////////////
//
// Program Option String
//

ProgramOptionString::ProgramOptionString( const std::string& name )
    : ProgramOption( name )
{
    ProgramOptionsManager::Instance()->AddStringOption( name );
}


ProgramOptionString::ProgramOptionString( const std::string& name, const std::string& defaultValue )
    : ProgramOption( name )
{
    ProgramOptionsManager::Instance()->AddStringOptionWithDefault( name, defaultValue );
}


std::string ProgramOptionString::ToString() const
{
    return ProgramOptionsManager::Instance()->GetStringOption( m_longName );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
