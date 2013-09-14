// Caramel C++ Library - Program Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Error/CatchException.h>
#include <Caramel/Program/ConsoleApplicationImpl.h>
#include <Caramel/Program/ProgramOptions.h>
#include <Caramel/Program/ProgramOptionsManager.h>
#include <Caramel/String/Algorithm.h>
#include <Caramel/String/Utf8String.h>

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )
#include <Caramel/Windows/DebuggerTraceListener.h>
#endif

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
//   ProgramOptions
//   ProgramOptionValue
//   ProgramOptionBool
//   ProgramOptionString
//   PositionalProgramOptionValues
//

///////////////////////////////////////////////////////////////////////////////
//
// Console Application
//

ConsoleApplication::ConsoleApplication()
    : m_impl( new ConsoleApplicationImpl )
{
}


ConsoleApplication::~ConsoleApplication()
{
}


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


//
// Implementation
// - The thread creating and destroying ConsoleApplication
//   should always be UI main thread.
//

ConsoleApplicationImpl::ConsoleApplicationImpl()
{
    auto stdoutListener = new Trace::StdoutListener;

    stdoutListener->BindBuiltinChannels( Trace::LEVEL_INFO );

    // Pass ownership to trace listener.
    Trace::Listeners::AddManaged( stdoutListener );

    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    {
        auto debuggerListener = new Windows::DebuggerTraceListener;

        debuggerListener->BindBuiltinChannels( Trace::LEVEL_DEBUG );

        Trace::Listeners::AddManaged( debuggerListener );
    }
    #endif // CARAMEL_SYSTEM_IS_WINDOWS
}


///////////////////////////////////////////////////////////////////////////////
//
// Program Options Manager
//

ProgramOptionsManager::ProgramOptionsManager()
    : m_positionalAdded( false )
{
}


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


void ProgramOptionsManager::AddPositionalOptions( const std::vector< ProgramOptionValue >& options )
{
    if ( m_positionalAdded )
    {
        CARAMEL_THROW( "Positional options can only be added once" );
    }

    for ( Uint i = 0; i < options.size(); ++ i )
    {
        m_positionalDesc.add( options[i].GetLongName().c_str(), 1 );
    }

    m_positionalAdded = true;
}


//
// Parsing
//

void ProgramOptionsManager::ParseCommandLine()
{
    namespace po = boost::program_options;

    m_arguments.clear();

    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    {
        // NOTES: split_winmain() suppose the parameter is the lpCmdLine in WinMain(),
        //        but the return value of GetCommandLine() has prepended the program path.
        //        We need to remove the first argument manually, therefore the for loop
        //        starts at 1, not 0.

        const std::vector< std::wstring > wargs = po::split_winmain( ::GetCommandLineW() );
        
        for ( Uint i = 1; i < wargs.size(); ++ i )
        {
            m_arguments.push_back( Utf8String( wargs[i] ).ToString() );
        }
    }
    #else
    {
        CARAMEl_NOT_IMPLEMETNED();
    }
    #endif


    po::store(
        po::command_line_parser( m_arguments )
            .options( m_optionsDesc )
            .positional( m_positionalDesc )
            .allow_unregistered()
            .run(),
        m_variablesMap
    );

    po::notify( m_variablesMap );
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
// Program Options
//

void ProgramOptions::ParseCommandLine()
{
    ProgramOptionsManager::Instance()->ParseCommandLine();
}


///////////////////////////////////////////////////////////////////////////////
//
// Program Option Value
//

ProgramOptionValue::ProgramOptionValue( const std::string& name )
{
    m_longName = Contains( name, ',' )
               ? BeforeFirst( name, ',' )
               : name;
}


Bool ProgramOptionValue::Exists() const
{
    return ProgramOptionsManager::Instance()->Contains( m_longName );
}


///////////////////////////////////////////////////////////////////////////////
//
// Program Option Bool
//

ProgramOptionBool::ProgramOptionBool( const std::string& name )
    : ProgramOptionValue( name )
{
    ProgramOptionsManager::Instance()->AddBoolOption( name );
}


///////////////////////////////////////////////////////////////////////////////
//
// Program Option String
//

ProgramOptionString::ProgramOptionString( const std::string& name )
    : ProgramOptionValue( name )
{
    ProgramOptionsManager::Instance()->AddStringOption( name );
}


ProgramOptionString::ProgramOptionString( const std::string& name, const std::string& defaultValue )
    : ProgramOptionValue( name )
{
    ProgramOptionsManager::Instance()->AddStringOptionWithDefault( name, defaultValue );
}


std::string ProgramOptionString::ToString() const
{
    return ProgramOptionsManager::Instance()->GetStringOption( m_longName );
}


///////////////////////////////////////////////////////////////////////////////
//
// Positional Program Option Values
//

PositionalProgramOptionValues::PositionalProgramOptionValues(
    const ProgramOptionValue& value1 )
{
    std::vector< ProgramOptionValue > values;
    values.push_back( value1 );

    ProgramOptionsManager::Instance()->AddPositionalOptions( values );
}


PositionalProgramOptionValues::PositionalProgramOptionValues(
    const ProgramOptionValue& value1,
    const ProgramOptionValue& value2 )
{
    std::vector< ProgramOptionValue > values;
    values.push_back( value1 );
    values.push_back( value2 );

    ProgramOptionsManager::Instance()->AddPositionalOptions( values );
}


PositionalProgramOptionValues::PositionalProgramOptionValues(
    const ProgramOptionValue& value1,
    const ProgramOptionValue& value2,
    const ProgramOptionValue& value3 )
{
    std::vector< ProgramOptionValue > values;
    values.push_back( value1 );
    values.push_back( value2 );
    values.push_back( value3 );

    ProgramOptionsManager::Instance()->AddPositionalOptions( values );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
