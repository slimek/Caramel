// Caramel C++ Library Test - Run Test Main Entry

#include "CaramelTestPch.h"

#include <Caramel/Program/ConsoleApplication.h>
#include <UnitTest++/UnitTest++.h>


///////////////////////////////////////////////////////////////////////////////
//
// Run Test
//

class RunTest : public ConsoleApplication
{
private:

    Int Main();
};


Int RunTest::Main()
{
    return UnitTest::RunAllTests();
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
