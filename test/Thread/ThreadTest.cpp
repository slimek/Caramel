// Caramel C++ Library Test - Thread - Thread Test

#include "CaramelTestPch.h"

#include <Caramel/Chrono/SecondClock.h>
#include <Caramel/Thread/ThisThread.h>
#include <Caramel/Thread/Thread.h>
#include <UnitTest++/UnitTest++.h>

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )
#include <Windows.h>
#endif

namespace Caramel
{

SUITE( ThreadSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Thread Test
//

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


TEST( ThreadIdTest )
{
    const Uint threadId = ThisThread::GetThreadId();

    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    CHECK( threadId == ::GetCurrentThreadId() );
    #endif
}


///////////////////////////////////////////////////////////////////////////////

}  // SUITE ThreadSuite

} // namespace Caramel
