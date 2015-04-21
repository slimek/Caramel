// Caramel C++ Library Test - Task - Task Completion Source Suite

#include "CaramelTestPch.h"

#include <Caramel/Task/StdAsync.h>
#include <Caramel/Task/TaskCompletionSource.h>
#include <Caramel/Thread/ThisThread.h>


namespace Caramel
{

SUITE( TaskCompletionSourceSuite )
{

TEST( TaskCompletionSourceTest )
{
    StdAsync async;

    TaskCompletionSource< Int > source1;

    auto task1 = source1.GetTask();
    async.Submit( "Source1 Task",
    [&]
    {
        ThisThread::SleepFor( Ticks( 100 ));
        source1.SetResult( 42 );
    });

    task1.Wait();

    CHECK( 42 == task1.GetResult() );


    TaskCompletionSource< std::string > source2;

    auto task2 = source2.GetTask();
    async.Submit( "Source2 Task",
    [&]
    {
        ThisThread::SleepFor( Ticks( 100 ));
        source2.SetResult( "Alice" );
    });

    task2.Wait();

    CHECK( "Alice" == task2.GetResult() );


    TaskCompletionSource< void > source3;

    auto task3 = source3.GetTask();
    async.Submit( "Source3 Task",
    [&]
    {
        ThisThread::SleepFor( Ticks( 100 ));
        source3.Set();
    });

    task3.Wait();
}


} // SUITE TaskCompletionSourceSuite

} // namespace Caramel
