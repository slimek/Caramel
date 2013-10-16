// Caramel C++ Library Test - Thread - Thread Test

#include "CaramelTestPch.h"

#include <Caramel/Chrono/SecondClock.h>
#include <Caramel/Thread/ThisThread.h>
#include <Caramel/Thread/Thread.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Thread Test
//

SUITE( ThreadSuite )
{

TEST( ThreadTest )
{
    Thread t0;

    Thread t1( "Execute1", [=] {} );
    t1.Join();

    TickClock clock;

    Thread t2( "Execute2", [=] { ThisThread::SleepFor( Ticks( 100 )); } );
    t2.Join();

    CHECK_CLOSE( clock.Slice(), Ticks( 110 ), Ticks( 10 ));

    Thread t3( "Execute3", [=] { ThisThread::SleepFor( Seconds( 0.1 )); } );
    t3.Join();

    CHECK_CLOSE( clock.Slice(), Ticks( 110 ), Ticks( 10 ));
}

}  // ThreadSuite



///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
