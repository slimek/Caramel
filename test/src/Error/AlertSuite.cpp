// Caramel C++ Library Test - Error - Alert Suite

#include "CaramelTestPch.h"

#include <Caramel/Error/Alert.h>
#include <Caramel/Error/Assert.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( AlertSuite )
{

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
    return ALERT_RESULT_CONTINUE;
}


TEST( AlertTest )
{
    auto oldHandler = SetAlertHandler( LocalAlertHandler );

    #if !defined( NDEBUG )
    {
        CARAMEL_ASSERT( 0 == 1 );

        CHECK( s_fileBuffer     == __FILE__ );
        CHECK( s_functionBuffer == __FUNCTION__ );
        CHECK( s_messageBuffer  == "0 == 1" );
    }
    #endif

    // Throw Handler

    SetAlertHandler( ThrowAlertHandler );

    try
    {
        CARAMEL_ALERT( "Hello Alert!" );
    }
    catch ( Exception& x )
    {
        CHECK( "Assert failed: Hello Alert!" == x.What() );
    }


    SetAlertHandler( oldHandler );
}


} // SUITE AlertSuite

} // namespace Caramel
