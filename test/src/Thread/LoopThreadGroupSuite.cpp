// Caramel C++ Library Test - Thread - Loop Thread Group Suite

#include "CaramelTestPch.h"

#include <Caramel/Thread/LoopThreadGroup.h>
#include <Caramel/Thread/ThisThread.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( LoopThreadGroupSuite )
{

TEST( LoopThreadGroupTest )
{
    LoopThreadGroup threads;

    Int count0 = 0;
    Int count1 = 0;
    Int count2 = 0;

    threads.Start( "Test0", [&] { ++ count0; }, Ticks( 0 ));
    threads.Start( "Test1", [&] { ++ count1; }, Ticks( 10 ));
    threads.Start( "Test2", [&] { ++ count2; }, Ticks( 10000 ));

    ThisThread::SleepFor( Ticks( 100 ));

    threads.StopAll();

    CHECK( 100 < count0 );
    CHECK_CLOSE( 10, count1, 2 );
    CHECK( 0 == count2 );
}


} // SUITE LoopThreadGroupSuite

} // namespace Caramel
