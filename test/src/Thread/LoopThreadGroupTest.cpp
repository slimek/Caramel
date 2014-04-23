// Caramel C++ Library Test - Thread - Loop Thread Group Test

#include "CaramelTestPch.h"

#include <Caramel/Thread/LoopThreadGroup.h>
#include <Caramel/Thread/ThisThread.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( LoopThreadGroupSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Loop Thread Group Test
//

TEST( LoopThreadGroupTest )
{
    LoopThreadGroup threads;

    Int count = 0;

    threads.Start( "Test0", [&] { ++ count; }, Ticks( 0 ));
    threads.Start( "Test1", [] {}, Ticks( 10 ));
    threads.Start( "Test2", [] {}, Ticks( 10000 ));

    ThisThread::SleepFor( Ticks( 100 ));

    threads.StopAll();

    CHECK( 0 < count );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE LoopThreadGroupSuite

} // namespace Caramel
