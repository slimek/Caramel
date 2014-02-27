// Caramel C++ Library Test - DateTime - DateTime-Boolean Test

#include "CaramelTestPch.h"

#include <Caramel/Chrono/TimedBool.h>
#include <Caramel/DateTime/DateTime.h>
#include <Caramel/Thread/ThisThread.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( DateTimeBoolSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// DateTime-Boolean Test
//

TEST( DateTimeBoolTest )
{
    TimedBool< DateTime > timer1( Seconds( 1 ));
    TimedBool< DateTime > timer2;

    timer2.Start( Days( 1 ));
    
    CHECK( false == timer1 );
    CHECK( false == timer2 );

    ThisThread::SleepFor( Seconds( 2 ));

    CHECK( true  == timer1 );
    CHECK( false == timer2 );

    timer1.Restart();
    timer2.ExpireNow();

    CHECK( false == timer1 );
    CHECK( true  == timer2 );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE DateTimeBoolSuite

} // namespace Caramel
