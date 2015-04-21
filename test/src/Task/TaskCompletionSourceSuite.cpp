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
    StdAsyncProxy async;

    TaskCompletionSource< Int > source1;

    auto task1 = source1.GetTask();
    async.Submit( "Source1 Task",
    [&]
    {
        ThisThread::SleepFor( Ticks( 100 ));
        source1.SetResult( 42 );
    });

    Int value1 = 0;
    auto then1 = task1.Then( [&] ( Int result ) { value1 = result; });
    then1.Wait();

    CHECK( 42 == value1 );


    TaskCompletionSource< std::string > source2;

    auto task2 = source2.GetTask();
    async.Submit( "Source2 Task",
    [&]
    {
        ThisThread::SleepFor( Ticks( 100 ));
        source2.SetResult( "Alice" );
    });

    std::string value2;
    auto then2 = task2.Then( [&] ( std::string result ) { value2 = result; });
    then2.Wait();

    CHECK( "Alice" == value2 );


    TaskCompletionSource< void > source3;

    auto task3 = source3.GetTask();
    async.Submit( "Source3 Task",
    [&]
    {
        ThisThread::SleepFor( Ticks( 100 ));
        source3.Set();
    });

    Bool done3 = false;
    auto then3 = task3.Then( [&] { done3 = true; });
    then3.Wait();
    
    CHECK( true == done3 );
}


} // SUITE TaskCompletionSourceSuite

} // namespace Caramel
