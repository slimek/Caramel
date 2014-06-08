// Caramel C++ Library Test - Task - Std Async Suite

#include "CaramelTestPch.h"

#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Task/StdAsync.h>
#include <Caramel/Thread/ThisThread.h>
#include <UnitTest++/UnitTest++.h>
#include <future>


namespace Caramel
{

SUITE( StdAsyncSuite )
{

TEST( StdAsyncTest )
{
    StdAsync executor;

    Task< void > t1( "Test1", [] {} );
    Task< Int >  t2( "Test2", [] { return 42; } );

    executor.Submit( t1 );
    executor.Submit( t2 );

    t1.Wait();
    t2.Wait();

    CHECK( 42 == t2.GetResult() );
}


} // SUITE StdAsyncSuite

} // namespace Caramel
