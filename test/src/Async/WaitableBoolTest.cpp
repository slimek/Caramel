// Caramel C++ Library Test - Async - Waitable Boolean Test

#include "CaramelTestPch.h"

#include <Caramel/Thread/Thread.h>
#include <Caramel/Thread/ThisThread.h>
#include <Caramel/Thread/WaitableBool.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( WaitableBoolSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Waitable Bool Test
//

TEST( WaitableBoolTest )
{
    // If the test failed, program would be blocked forever.

    WaitableBool flag( false );

    Thread t1( "Test1", [&]
    {
        flag.Wait();
    });

    ThisThread::SleepFor( Ticks( 500 ));
    flag = true;
    t1.Join();
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE WaitableBoolSuite

} // namespace Caramel
