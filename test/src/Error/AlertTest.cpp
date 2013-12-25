// Caramel C++ Library Test - Error - Alert Test

#include "CaramelTestPch.h"

#include <Caramel/Error/Alert.h>
#include <Caramel/Error/Assert.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( AlertSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Alert Test
//

static std::string s_fileBuffer;
static std::string s_functionBuffer;
static std::string s_messageBuffer;

AlertResult LocalAlertHandler(
    Int line, const std::string& file, const std::string& function,
    const std::string& messgae )
{
    s_fileBuffer = file;
    s_functionBuffer = function;
    s_messageBuffer = messgae;
    return ALERT_RESULT_CONTINUE_ALL;
}


TEST( AlertTest )
{
    SetAlertHandler( LocalAlertHandler );

    CARAMEL_ASSERT( 0 == 1 );

    CHECK( s_fileBuffer     == __FILE__ );
    CHECK( s_functionBuffer == __FUNCTION__ );
    CHECK( s_messageBuffer  == "0 == 1" );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE AlertSuite

} // namespace Caramel
