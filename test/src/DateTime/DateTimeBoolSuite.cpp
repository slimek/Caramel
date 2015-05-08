// Caramel C++ Library Test - DateTime - DateTime-Boolean Suite

#include "CaramelTestPch.h"

#include <Caramel/Chrono/TimedBool.h>
#include <Caramel/DateTime/DateTime.h>
#include <Caramel/Thread/ThisThread.h>


namespace Caramel
{

SUITE( DateTimeBool )
{

//
// DateTime provides sufficient stuff to be used by TimedBool
//
//   ClockType, TimePoint : DateTime
//   Duration             : TimeSpan
//

TEST( DateTimeBool )
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


} // SUITE DateTimeBool

} // namespace Caramel
