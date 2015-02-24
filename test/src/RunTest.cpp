// Caramel C++ Library Test - Run Test Main Entry

#include "CaramelTestPch.h"

#include "Utils/AssetReader.h"
#include <Caramel/Error/Alert.h>
#include <Caramel/FileSystem/Path.h>
#include <Caramel/Program/ConsoleApplication.h>
#include <Caramel/Program/ProgramOptions.h>
#include <UnitTest++/TestReporterStdout.h>
#include <iostream>

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )
// You may remove this header if you did not install Visual Leak Detector.
#include <vld.h>
#endif


///////////////////////////////////////////////////////////////////////////////
//
// Run Test
//

static ProgramOptionString po_suiteName( "name" );

static PositionalProgramOptionValues po_positional( po_suiteName );

class RunTest : public ConsoleApplication
{
private:

    Int Main();
};


Int RunTest::Main()
{
    ProgramOptions::ParseArguments( this->GetArguments() );

    SetAlertHandler( ThrowAlertHandler );

    Int result = 0;
    
    if ( po_suiteName.Exists() )
    {
        cout << "Run Suite : " << po_suiteName << endl;

    	UnitTest::TestReporterStdout reporter;
	    UnitTest::TestRunner runner( reporter );

        result = runner.RunTestsIf(
            UnitTest::Test::GetTestList(),
            po_suiteName.ToString().c_str(),
            UnitTest::True(),
            0
        );
    }
    else
    {
        result = UnitTest::RunAllTests();
    }

    cin.get();

    return result;
}


///////////////////////////////////////////////////////////////////////////////
//
// Main Entry
//

int main( int argc, char* argv[] )
{
    RunTest app;
    return app.Run( argc, argv );
}


///////////////////////////////////////////////////////////////////////////////
//
// Utilities
//

namespace Caramel
{

AssetReader::AssetReader( const std::string& fileName )
    : m_file( Path( "../assets" ) / fileName )
    , m_reader( m_file )
{}


Bool AssetReader::ReadLine( std::string& line )
{
    return m_reader.ReadLine( line );
}


} // namespace Caramel


///////////////////////////////////////////////////////////////////////////////
