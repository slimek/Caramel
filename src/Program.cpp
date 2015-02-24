// Caramel C++ Library - Program Facility - Implementation

#include "CaramelPch.h"

#include "Program/ConsoleApplicationImpl.h"
#include "Program/ProgramOptionsManager.h"
#include <Caramel/Error/CatchException.h>
#include <Caramel/Program/ProgramOptions.h>
#include <Caramel/String/Algorithm.h>
#include <Caramel/String/Utf8String.h>

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )
#include <Caramel/Windows/DebuggerTraceAdapter.h>
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
        TraceError( xc.TracingMessage() );

        std::cout << std::endl
                  << "Program caught an exception and exit abnormally." << std::endl;
        std::cin.get();
    }
    return xc.Result();
}


Int ConsoleApplication::Run( Int argc, Char* argv[] )
{
    m_impl->BuildArguments( argc, argv );

    return this->Run();
}


std::vector< std::string > ConsoleApplication::GetArguments() const
{
    return m_impl->GetArguments();
}


//
// Implementation
// - The thread creating and destroying ConsoleApplication
//   should always be UI main thread.
//

ConsoleApplicationImpl::ConsoleApplicationImpl()
{
    auto stdoutListener = new Trace::StdoutAdapter;

    stdoutListener->BindBuiltinChannels( Trace::LEVEL_INFO );

    // Pass ownership to trace listener.
    Trace::Listeners::AddManaged( stdoutListener );

    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    {
        auto debuggerListener = new Windows::DebuggerTraceAdapter;

        debuggerListener->BindBuiltinChannels( Trace::LEVEL_DEBUG );

        Trace::Listeners::AddManaged( debuggerListener );
    }
    #endif // CARAMEL_SYSTEM_IS_WINDOWS
}


void ConsoleApplicationImpl::BuildArguments( Int argc, Char* argv[] )
{
    CARAMEL_ASSERT( 1 <= argc );

    // The first argument is program path, we don't need it

    for ( Int i = 1; i < argc; ++ i )
    {
        m_arguments.push_back( std::string( argv[i] ));
    }
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

    for ( const auto& option : options )
    {
        m_positionalDesc.add( option.GetLongName().c_str(), 1 );
    }

    m_positionalAdded = true;
}


//
// Parsing
//

void ProgramOptionsManager::ParseArguments( const std::vector< std::string >& arguments )
{
    namespace po = boost::program_options;

    m_arguments = arguments;

    auto parser = po::command_line_parser( m_arguments )
                 .options( m_optionsDesc )
                 .allow_unregistered();

    if ( m_positionalAdded )
    {
        parser.positional( m_positionalDesc );
    }

    po::store( parser.run(), m_variablesMap );

    po::notify( m_variablesMap );
}


#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

void ProgramOptionsManager::ParseCommandLine()
{
    namespace po = boost::program_options;

    std::vector< std::string > arguments;

    // NOTES: split_winmain() suppose the parameter is the lpCmdLine in WinMain(),
    //        but the return value of GetCommandLine() has prepended the program path.
    //        We need to remove the first argument manually, therefore the for loop
    //        starts at 1, not 0.

    const std::vector< std::wstring > wargs = po::split_winmain( ::GetCommandLineW() );
        
    // Omit the first argument.
    for ( Uint i = 1; i < wargs.size(); ++ i )
    {
        arguments.push_back( Utf8String( wargs[i] ).ToString() );
    }

    this->ParseArguments( arguments );
}

#endif // CARAMEL_SYSTEM_IS_WINDOWS



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
        CARAMEL_THROW( "Option not found, longName: {0}", longName );
    }

    return m_variablesMap[ longName ].as< std::string >();
}


///////////////////////////////////////////////////////////////////////////////
//
// Program Options
//

void ProgramOptions::ParseArguments( const std::vector< std::string >& arguments )
{
    ProgramOptionsManager::Instance()->ParseArguments( arguments );
}


#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

void ProgramOptions::ParseCommandLine()
{
    ProgramOptionsManager::Instance()->ParseCommandLine();
}

#endif // CARAMEL_SYSTEM_IS_WINDOWS


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
