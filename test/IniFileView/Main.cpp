// Caramel C++ Library - INI File View Test

#include <Caramel/Error/Assert.h>
#include <Caramel/FileView/IniFileView.h>
#include <Caramel/Program/ConsoleApplication.h>
#include <iostream>
#include <vector>


using namespace std;
using namespace Caramel;


///////////////////////////////////////////////////////////////////////////////
//
// INI File View Test
//

class IniFileViewTest : public ConsoleApplication
{
private:

    Int Main();
};


Int IniFileViewTest::Main()
{
    IniFileView iniFile( "Test.ini" );


    //
    // Array Values
    //

    IniSection as = iniFile.GetSection( "Arrays" );

    vector< string > empty;

    CARAMEL_CHECK( empty == as.GetStringArrayValue( "EmptyArray1" ));
    CARAMEL_CHECK( empty == as.GetStringArrayValue( "EmptyArray2" ));


    cout << "Program exit successfully" << endl;
    cin.get();

    return EXIT_SUCCESS;
}


///////////////////////////////////////////////////////////////////////////////
//
// Main Entry
//

int main()
{
    IniFileViewTest app;
    return app.Run();
}


///////////////////////////////////////////////////////////////////////////////
