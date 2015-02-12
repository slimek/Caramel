// Caramel C++ Library Test - Thread - Waitable Boolean Suite

#include "CaramelTestPch.h"

#include <Caramel/Thread/Thread.h>
#include <Caramel/Thread/ThisThread.h>
#include <Caramel/Thread/WaitableBool.h>


namespace Caramel
{

SUITE( WaitableBoolSuite )
{

TEST( WaitableBoolTest )
{
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

    {
        WaitableBool flag( false );

        Bool v1 = false;
        Bool v2 = false;

        // This should go timeout
        Thread t1( "Test1", [&]
        {
            v1 = flag.WaitFor( Ticks( 10 ));
        });

        // This should triggered
        Thread t2( "Test2", [&]
        {
            v2 = flag.WaitFor( Ticks( 500 ));
        });

        ThisThread::SleepFor( Ticks( 100 ));
        flag = true;
        t1.Join();
        t2.Join();

        CHECK( false == v1 );
        CHECK( true  == v2 );
    }
}


} // SUITE WaitableBoolSuite

} // namespace Caramel
