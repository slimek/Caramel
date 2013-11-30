// Caramel C++ Library Test - Run Test Main Entry

#include "CaramelTestPch.h"

#include <Caramel/Program/ConsoleApplication.h>
#include <Caramel/Program/ProgramOptions.h>
#include <UnitTest++/UnitTest++.h>
#include <UnitTest++/TestReporterStdout.h>
#include <iostream>


using namespace std;

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
    ProgramOptions::ParseCommandLine();

    Int result = 0;
    
    if ( po_suiteName.Exists() )
    {
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

int main()
{
    RunTest app;
    return app.Run();
}


///////////////////////////////////////////////////////////////////////////////
