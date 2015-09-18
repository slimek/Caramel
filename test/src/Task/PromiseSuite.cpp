// Caramel C++ Library Test - Task - Promise Suite

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEventSlot.h>
#include <Caramel/Async/AnyEventTask.h>
#include <Caramel/Concurrent/Queue.h>
#include <Caramel/Task/Promise.h>
#include <Caramel/Task/AsyncSubmit.h>
#include <Caramel/Task/WorkerThread.h>
#include <Caramel/Thread/ThisThread.h>


namespace Caramel
{

SUITE( Promise )
{

TEST( Promise )
{
    Promise< Int > promise1( "Big answer" );  // Give the task name.

    auto task1 = promise1.GetTask();
    AsyncSubmit( "Promise1 Task",
    [&]
    {
        ThisThread::SleepFor( Ticks( 100 ));
        promise1.RunTask( 42 );
    });

    Int value1 = 0;
    auto then1 = task1.Then( [&] ( Int result ) { value1 = result; });
    then1.Wait();

    CHECK( "Big answer" == task1.Name() );
    CHECK( "Big answer-Then" == then1.Name() );
    CHECK( 42 == value1 );


    Promise< std::string > promise2;

    auto task2 = promise2.GetTask();
    AsyncSubmit( "Promise2 Task",
    [&]
    {
        ThisThread::SleepFor( Ticks( 100 ));
        promise2.RunTask( "Alice" );
    });

    std::string value2;
    auto then2 = task2.Then( [&] ( std::string result ) { value2 = result; });
    then2.Wait();

    CHECK( "Alice" == value2 );


    Promise< void > promise3;

    auto task3 = promise3.GetTask();
    AsyncSubmit( "Promise3 Task",
    [&]
    {
        ThisThread::SleepFor( Ticks( 100 ));
        promise3.RunTask();
    });

    Bool done3 = false;
    auto then3 = task3.Then( [&] { done3 = true; });
    then3.Wait();
    
    CHECK( true == done3 );
}


TEST( PromiseWithExecutor )
{
    WorkerThread worker( "Promise worker" );

    Promise< std::string > promise1;

    auto task1 = promise1.GetTask();
    AsyncSubmit(
    [&]
    {
        ThisThread::SleepFor( Ticks( 50 ));
        promise1.RunTask( "Marisa", worker );
    });

    std::string value1;
    auto then1 = task1.Then( [&] ( std::string result ) { value1 = result; });
    then1.Wait();

    CHECK( "Marisa" == value1 );


    Promise< void > promise2;

    auto task2 = promise2.GetTask();
    AsyncSubmit(
    [&]
    {
        ThisThread::SleepFor( Ticks( 50 ));
        promise2.RunTask( worker );
    });

    Bool done2 = false;
    auto then2 = task2.Then( [&] { done2 = true; });
    then2.Wait();

    CHECK( true == done2 );

    worker.Stop();
}


TEST( PromiseWithAnyEvent )
{
    Promise< AnyEvent > promise;

    AnyEventTask task = promise.GetTask();
    AsyncSubmit(
    [&]
    {
        promise.RunTask( AnyEvent( 2, "Reimu" )); 
    });

    AnyEventSlot slot;
    task.Link( slot );
    
    // NOTES: AnyEventTask send event to target in a Then task.
    //        task.Wait() may execute before the Then task and doesn't fit here.
    slot.Wait();

    CHECK( 2 == slot.Id() );
    CHECK( "Reimu" == slot.Value< std::string >() );
}


TEST( PromiseInOutContainer )
{
    Concurrent::Queue< Promise< Int >> promises;
    Task< Int > task;

    // Part 1
    {
        Promise< Int > promise;
        task = promise.GetTask();
        promises.Push( promise );
    }

    // Part 2
    {
        Promise< Int > promise;
        CHECK( true == promises.TryPop( promise ));
        promise.RunTask( 51 );
    }

    task.Wait();
    CHECK( 51 == task.GetResult() );
}


} // SUITE Promise

} // namespace Caramel
