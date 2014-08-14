// Caramel C++ Library Test - Thread - Thread Suite

#include "CaramelTestPch.h"

#include <Caramel/Chrono/SecondClock.h>
#include <Caramel/Thread/ThisThread.h>
#include <Caramel/Thread/Thread.h>
#include <Caramel/Thread/WaitableBool.h>
#include <UnitTest++/UnitTest++.h>

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )
#include <Windows.h>
#endif

#include <thread>

namespace Caramel
{

SUITE( ThreadSuite )
{

TEST( ThreadTest )
{
    Thread t0;

    Thread t1( "Execute1", [=] {} );
    t1.Join();

    TickWatch watch;

    Thread t2( "Execute2", [=] { ThisThread::SleepFor( Ticks( 100 )); } );
    t2.Join();

    CHECK_CLOSE( watch.Slice(), Ticks( 110 ), Ticks( 10 ));

    Thread t3( "Execute3", [=] { ThisThread::SleepFor( Seconds( 0.1 )); } );
    t3.Join();

    CHECK_CLOSE( watch.Slice(), Ticks( 110 ), Ticks( 10 ));
}


TEST( ThreadIdTest )
{
    /// Current Thread ///

    auto threadId = ThisThread::GetId();

    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    {
        const Uint32 curId = ::GetCurrentThreadId();

        CHECK( threadId.GetNativeId() == curId );
        CHECK( threadId.ToString() == Sprintf( "%u", curId ));
    }
    #endif

    /// Operators ///

    // Both are "not a thread"
    ThreadId id01;
    ThreadId id02;
    
    CHECK( id01 == id02 );
    CHECK( false == ( id01 < id02 ));
    CHECK( false == ( id02 < id01 ));

    CHECK( id01 != threadId );
    CHECK( id01 <  threadId );


    /// Compare with Another Thread ///

    ThreadId t1Id;
    WaitableBool ready;
    Bool checked = false;

    Thread t1( "Test1", [&]
    {
        ready.Wait();
        checked = ( t1Id == ThisThread::GetId() );
    });

    t1Id = t1.GetId();
    ready = true;

    t1.Join();

    CHECK( checked );
}


#if ! defined( CARAMEL_SYSTEM_OF_APPLE )

TEST( ThisThreadAtExitTest )
{
    WaitableBool gate;
    Bool flag = false;

    Thread t1( "AtExit",
    [&]
    {
        ThisThread::AtThreadExit(
        [&]
        {
            flag = true;
        });

        gate.Wait();
    });

    CHECK( false == flag );

    gate = true;
    t1.Join();

    CHECK( true == flag );
}

#endif // CARAMEL_SYSTEM_OF_APPLE


}  // SUITE ThreadSuite

} // namespace Caramel
