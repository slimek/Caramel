// Caramel C++ Library Test - Task - Task Completion Source Suite

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEventSlot.h>
#include <Caramel/Async/AnyEventTask.h>
#include <Caramel/Concurrent/Queue.h>
#include <Caramel/Task/StdAsync.h>
#include <Caramel/Task/TaskCompletionSource.h>
#include <Caramel/Task/WorkerThread.h>
#include <Caramel/Thread/ThisThread.h>


namespace Caramel
{

SUITE( TaskCompletionSourceSuite )
{

TEST( TaskCompletionSourceTest )
{
    TaskCompletionSource< Int > source1( "Big answer" );

    auto task1 = source1.GetTask();
    StdAsync::Submit( "Source1 Task",
    [&]
    {
        ThisThread::SleepFor( Ticks( 100 ));
        source1.RunTask( 42 );
    });

    Int value1 = 0;
    auto then1 = task1.Then( [&] ( Int result ) { value1 = result; });
    then1.Wait();

    CHECK( "Big answer" == task1.Name() );
    CHECK( "Big answer-Then" == then1.Name() );
    CHECK( 42 == value1 );


    TaskCompletionSource< std::string > source2;

    auto task2 = source2.GetTask();
    StdAsync::Submit( "Source2 Task",
    [&]
    {
        ThisThread::SleepFor( Ticks( 100 ));
        source2.RunTask( "Alice" );
    });

    std::string value2;
    auto then2 = task2.Then( [&] ( std::string result ) { value2 = result; });
    then2.Wait();

    CHECK( "Alice" == value2 );


    TaskCompletionSource< void > source3;

    auto task3 = source3.GetTask();
    StdAsync::Submit( "Source3 Task",
    [&]
    {
        ThisThread::SleepFor( Ticks( 100 ));
        source3.RunTask();
    });

    Bool done3 = false;
    auto then3 = task3.Then( [&] { done3 = true; });
    then3.Wait();
    
    CHECK( true == done3 );
}


TEST( TaskCompletionSourceWithExecutorTest )
{
    WorkerThread worker( "TaskCompletionSource worker" );

    TaskCompletionSource< std::string > source1;

    auto task1 = source1.GetTask();
    StdAsync::Submit(
    [&]
    {
        ThisThread::SleepFor( Ticks( 50 ));
        source1.RunTask( "Marisa", worker );
    });

    std::string value1;
    auto then1 = task1.Then( [&] ( std::string result ) { value1 = result; });
    then1.Wait();

    CHECK( "Marisa" == value1 );


    TaskCompletionSource< void > source2;

    auto task2 = source2.GetTask();
    StdAsync::Submit(
    [&]
    {
        ThisThread::SleepFor( Ticks( 50 ));
        source2.RunTask( worker );
    });

    Bool done2 = false;
    auto then2 = task2.Then( [&] { done2 = true; });
    then2.Wait();

    CHECK( true == done2 );

    worker.Stop();
}


TEST( TaskCompletionSourceWithAnyEventTest )
{
    TaskCompletionSource< AnyEvent > source;

    AnyEventTask task = source.GetTask();
    StdAsync::Submit(
    [&]
    {
        source.RunTask( AnyEvent( 2, "Reimu" )); 
    });

    AnyEventSlot slot;
    task.Link( slot );
    
    // NOTES: AnyEventTask send event to target in a Then task.
    //        task.Wait() may execute before the Then task and doesn't fit here.
    slot.Wait();

    CHECK( 2 == slot.Id() );
    CHECK( "Reimu" == slot.Value< std::string >() );
}


TEST( TaskCompletionSourceInOutContainerTest )
{
    Concurrent::Queue< TaskCompletionSource< Int >> sources;
    Task< Int > task;

    // Part 1
    {
        TaskCompletionSource< Int > source;
        task = source.GetTask();
        sources.Push( source );
    }

    // Part 2
    {
        TaskCompletionSource< Int > source;
        CHECK( true == sources.TryPop( source ));
        source.RunTask( 51 );
    }

    task.Wait();
    CHECK( 51 == task.GetResult() );
}


} // SUITE TaskCompletionSourceSuite

} // namespace Caramel
