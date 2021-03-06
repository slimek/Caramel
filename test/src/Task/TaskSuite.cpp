// Caramel C++ Library Test - Task - Task Suite

#include "CaramelTestPch.h"

#include "Utils/StdVectorUtils.h"
#include <Caramel/Error/CatchException.h>
#include <Caramel/Task/AsyncSubmit.h>
#include <Caramel/Task/Task.h>
#include <Caramel/Task/TaskPoller.h>
#include <Caramel/Task/WorkerThread.h>
#include <Caramel/Thread/ThisThread.h>
#include <atomic>
#include <functional>
#include <vector>


namespace Caramel
{

SUITE( Task )
{

static Bool s_calledFoo = false;
static Bool s_calledQuz = false;

void Foo() { s_calledFoo = true; }
Int  Quz() { s_calledQuz = true; return 1; }


TEST( TaskTrivial )
{
    /// Not a Task ///

    Task< void > t0;

    CHECK( false        == t0.IsValid() );
    CHECK( true         == t0.IsIdle() );
    CHECK( "Not-a-task" == t0.Name() );
    CHECK( false        == t0.HasDelay() );
    CHECK( Ticks( 0 )   == t0.GetDelayDuration() );

    CHECK_THROW( t0.DelayFor( Ticks( 100 )), Caramel::Exception );
    CHECK_THROW( t0.Run(), Caramel::Exception );


    Task< Int > t1;

    CHECK( false        == t1.IsValid() );
    CHECK( true         == t1.IsIdle() );
    CHECK( "Not-a-task" == t1.Name() );
    CHECK( false        == t1.HasDelay() );
    CHECK( Ticks( 0 )   == t1.GetDelayDuration() );

    CHECK_THROW( t1.DelayFor( Ticks( 100 )), Caramel::Exception );
    CHECK_THROW( t1.Run(), Caramel::Exception );


    /// Assign a task to replace the "Not a Task" ///

    t0 = MakeTask( "Foo", &Foo );

    CHECK( true       == t0.IsValid() );
    CHECK( false      == t0.IsIdle() );
    CHECK( "Foo"      == t0.Name() );
    CHECK( false      == t0.HasDelay() );
    CHECK( Ticks( 0 ) == t0.GetDelayDuration() );

    t0.DelayFor( Ticks( 100 ));

    CHECK( true         == t0.HasDelay() );
    CHECK( Ticks( 100 ) == t0.GetDelayDuration() );

    WorkerThread worker( "TaskTrivial" );
    worker.Submit( t0 );
    t0.Wait();

    CHECK( true == t0.IsIdle() );
    CHECK( true == t0.IsDone() );

    worker.Stop();
}


class Widget
{
public:
    Widget() : m_ranBar( false ) {}

    void Bar() { m_ranBar = true; }

    Bool IsRanBar() const { return m_ranBar; }

private:
    Bool m_ranBar;    
};


TEST( TaskMemberFunction )
{
    Widget w;

    auto t2 = MakeTask( "Widget::Bar", std::bind( &Widget::Bar, &w ));
    auto t3 = MakeTask( "Widget::Bar", [&] { w.Bar(); });

    std::shared_ptr< Widget > pw( new Widget );

    auto t4 = MakeTask( "Widget::Bar", std::bind( &Widget::Bar, pw ));
    auto t5 = MakeTask( "Widget::Bar", [=] { pw->Bar(); });

    auto memFn = std::bind( &Widget::Bar, &w );

    auto t6 = MakeTask( "Widget::Bar", memFn );  // l-value function is Ok.
}


TEST( TaskOfBindMacro )
{
    /// Member Functions ///

    Widget w;

    auto bar = CARAMEL_TASK_OF_BIND( Widget::Bar, &w );

    CHECK( "Widget::Bar" == bar.Name() );

    bar.Run();

    CHECK( true == w.IsRanBar() );


    /// Stand-alone Functions ///

    s_calledFoo = false;

    auto foo = CARAMEL_TASK_OF_BIND( Foo );  // No arguments is Ok!

    CHECK( "Foo" == foo.Name() );

    foo.Run();

    CHECK( true == s_calledFoo );
}


TEST( TaskWithResult )
{
    auto itask = MakeTask( "IntTask", [] { return 42; } );

    itask.Run();
    CHECK( 42 == itask.GetResult() );

    auto stask = MakeTask( "StrTask", [] { return std::string( "Alice" ); } );

    stask.Run();
    CHECK( "Alice" == stask.GetResult() );
}


TEST( TaskWithException )
{
    std::string what;


    /// Exception in Wait() ///

    auto task1 = MakeTask( "BadTask1", [] { throw std::runtime_error( "bad1" ); } );
    AsyncSubmit( task1 );

    try
    {
        task1.Wait();
    }
    catch ( std::exception& x )
    {
        what = x.what();
    }

    CHECK( "bad1" == what );


    /// Exception in GetResult() ///

    Task< Int > task2 = MakeTask( "BadTask2", [] { throw std::runtime_error( "bad2" ); return 42; } );
    AsyncSubmit( task2 );

    try
    {
        task2.GetResult();
    }
    catch ( std::exception& x )
    {
        what = x.what();
    }

    CHECK( "bad2" == what );
}


TEST( TaskWaitOrCatch )
{
    std::string what;

    auto task1 = MakeTask( "Task1", [] {} );
    AsyncSubmit( task1 );


    /// Ran to Completing ///

    const auto result1 = task1.Catch();

    CHECK( TASK_STATE_RAN_TO_COMP == result1.doneState );
    CHECK( "Task1" == result1.name );
    CHECK( ! result1.anyFailure );
    CHECK( ! result1.exception );


    /// Fault with std::exception ///

    auto task2 = MakeTask( "Task2", [] { throw std::runtime_error( "bad" ); } );
    AsyncSubmit( task2 );

    const auto result2 = task2.Catch();

    CHECK( TASK_STATE_FAULTED == result2.doneState );
    CHECK( "Task2" == result2.name );
    CHECK( ! result2.anyFailure );
    CHECK( result2.exception );

    CHECK( nullptr == result2.anyFailure.operator->() );


    /// Fault with AnyFailure ///

    auto task3 = MakeTask( "Task3", [] { throw AnyFailure( 42, "Cirno" ); } );
    AsyncSubmit( task3 );

    const auto result3 = task3.Catch();

    CHECK( TASK_STATE_FAULTED == result3.doneState );
    CHECK( "Task3" == result3.name );
    CHECK( result3.anyFailure );
    CHECK( result3.exception );

    CHECK( 42      == result3.anyFailure->Code() );
    CHECK( "Cirno" == result3.anyFailure->Value< std::string >() );
}


TEST( TaskThen )
{
    Int count1 = 0;

    auto task1 = MakeTask( "Task1", [&] { ++ count1; } );
    auto task1c = task1.Then( "Task1+Continue", [&] { ++ count1; } );

    CHECK( true  == task1c.IsValid() );
    CHECK( false == task1c.IsIdle() );
    CHECK( "Task1+Continue" == task1c.Name() );

    AsyncSubmit( task1 );
    task1c.Wait();

    CHECK( 2 == count1 );
    

    /// Continuation Task uses a default name ///

    Int count2 = 0;

    auto task2 = MakeTask( "Task2", [&] { ++ count2; } );
    auto task2c = task2.Then( [&] { ++ count2; } );

    CHECK( "Task2-Then" == task2c.Name() );

    AsyncSubmit( task2 );
    task2c.Wait();

    CHECK( 2 == count2 );


    /// Continuatioin Task with return values ///

    auto task3 = MakeTask( "Task3", [] {} );
    auto task3c = task3.Then( [] { return 42; } );
    auto task3d = task3c.Then( [] { return std::string( "Cirno" ); } );

    CHECK( "Task3-Then-Then" == task3d.Name() );

    AsyncSubmit( task3 );
    task3d.Wait();

    CHECK( 42 == task3c.GetResult() );
    CHECK( "Cirno" == task3d.GetResult() );


    /// Continue a task after it is faulted

    auto task4 = MakeTask( "Task4", [] { CARAMEL_THROW( "Bad task" ); } );
    AsyncSubmit( task4 );

    task4.Catch();

    CHECK( true == task4.IsFaulted() );

    Bool faulted = false;

    auto task4c = task4.Then( "Task4-Faulted",
    [&] ( const Task< void >& task )
    {
        faulted = task.IsFaulted();
    });

    task4c.Wait();

    CHECK( true == faulted );


    /// Catch in Then ///

    auto task5 = MakeTask( "Task5", [] {} );
    TaskCore::CatchResult result5;

    auto then5 = task5.Then(
    [&] ( const Task< void >& task )
    {
        result5 = task.Catch(); 
    });

    AsyncSubmit( task5 );
    then5.Wait();

    CHECK( TASK_STATE_RAN_TO_COMP == result5.doneState );
    CHECK( "Task5" == result5.name );
    CHECK( ! result5.anyFailure );
    CHECK( ! result5.exception );

    CHECK( "Task5-Then" == then5.Name() );


    /// Continuation with Value ///

    auto task6 = MakeTask( "Task6", [] { return std::string( "Youmu" ); });

    // by task
    auto then6t = task6.Then( [] ( const Task< std::string >& task ) { return task.GetResult(); } );

    // by const reference
    auto then6r = task6.Then( [] ( const std::string& name ) -> std::string { return name + "-ref"; } );

    // by copy
    auto then6c = task6.Then( [] ( std::string name ) { return name + "-copy"; } );

    AsyncSubmit( task6 );
    then6t.Wait();
    then6r.Wait();
    then6c.Wait();

    CHECK( "Youmu"      == then6t.GetResult() );
    CHECK( "Youmu-ref"  == then6r.GetResult() );
    CHECK( "Youmu-copy" == then6c.GetResult() );


    // If faulted, all by-value continuations should be canceled

    auto task7 = MakeTask( "Task7", [] () -> Int { throw AnyFailure( 42 ); });
    auto then7 = task7.Then( [] ( Int value ) { return value; });

    AsyncSubmit( task7 );

    // ATTENTION: If a task throws, you must handle the exception by:
    //            1. Call Wait() or Catch(). or
    //            2. Give it a by-task continuation.
    task7.Catch();

    then7.Wait();

    CHECK( true == then7.IsCanceled() );
}


TEST( TaskContinueImmediately )
{
    /// The First Continuation should be executed immediately ///

    // Expected execute order:
    //      task  (Submit)
    //   >> taskc (Continue)
    //   >> taske (Submit)
    //
    //   Because task delayed for 100 ms, submit of taske is faster than continue of taskc.
    //   But taskc should run before task4e.

    WorkerThread worker( "Immediately" );

    std::vector< Int > seq;

    auto task = MakeTask( "Task", [&] { seq.push_back( 1 ); ThisThread::SleepFor( Ticks( 100 )); } );
    auto taskc = task.Then( [&] { seq.push_back( 2 ); } );
    auto taske = MakeTask( "Task4d", [&] { seq.push_back( 3 ); } );

    worker.Submit( task );
    worker.Submit( taske );

    taskc.Wait();
    taske.Wait();

    CHECK( 3 == seq.size() );
    CHECK( IsSorted( seq ));

    worker.Stop();
}


TEST( TaskCancel )
{
    // If a task is canceled, all its continuations should also be canceled. 

    auto task = MakeTask( [] { return 42; });
    auto thenV = task.Then( [] {} );
    auto thenR = task.Then( [] ( Int result ) {} );
    auto thenT = task.Then( [] ( const Task< Int >& task ) {} );

    task.Cancel();
    AsyncSubmit( task );

    thenV.Wait();
    thenR.Wait();
    thenT.Wait();

    CHECK( task.IsCanceled() );
    CHECK( thenV.IsCanceled() );
    CHECK( thenR.IsCanceled() );
    CHECK( thenT.IsCanceled() );

    // Other properties
    CHECK( task.IsDone() );
    CHECK( task.IsIdle() );

    // Tasks added after canceling should also be canceled.
    auto thenC = task.Then( [] {} );
    thenC.Wait();
    CHECK( thenC.IsCanceled() );
}


TEST( TaskFault )
{
    // If a task is faulted :
    // - Value-base continuation is canceled
    //   Task-based continuation is run, and GetResult() will throw the exception.

    auto task = MakeTask( [] () -> std::string { throw AnyFailure( 51 ); });
    auto thenV = task.Then( [] {} );
    auto thenR = task.Then( [] ( const std::string& result ) {} );
    auto thenT = task.Then( [] ( const Task< std::string >& task ) {} );

    AsyncSubmit( task );
    task.Catch();

    thenV.Wait();
    thenR.Wait();
    thenT.Wait();

    CHECK( task.IsFaulted() );
    CHECK( thenV.IsCanceled() );
    CHECK( thenR.IsCanceled() );
    CHECK( thenT.IsDone() && ! thenT.IsCanceled() && ! thenT.IsFaulted() );

    // Other properties
    CHECK( task.IsDone() );
    CHECK( task.IsIdle() );
}


TEST( TaskWithoutName )
{
    /// Standalone Functions ///

    auto t1 = MakeTask( &Foo );

    CHECK( true == t1.IsValid() );
    CHECK( ""   == t1.Name() );

    auto t2 = MakeTask( &Quz );

    CHECK( true == t2.IsValid() );
    CHECK( ""   == t2.Name() );

    t2.Run();

    CHECK( 1 == t2.GetResult() );


    /// Member Functions ///

    Widget w;

    auto t3 = MakeTask( std::bind( &Widget::Bar, &w ));

    CHECK( true == t3.IsValid() );
    CHECK( ""   == t3.Name() );


    /// Lambads ///

    auto t4 = MakeTask( [] { return std::string( "Reimu" ); } );

    CHECK( true == t4.IsValid() );
    CHECK( ""   == t4.Name() );

    t4.Run();

    CHECK( "Reimu" == t4.GetResult() );


    /// Catch Exception ///

    auto t5 = MakeTask( [] { throw AnyFailure( 42 ); } );

    t5.Run();
    auto r5 = t5.Catch();

    CHECK( r5.exception );   // true
    CHECK( r5.anyFailure );  // true
    CHECK( "" == r5.name );


    /// Continuation ///

    Int count = 0;

    auto t6 = MakeTask( [&] { ++ count; } );
    auto t6c = t6.Then( [] { return 42; } );

    CHECK( "" == t6c.Name() );

    AsyncSubmit( t6 );
    t6c.Wait();

    CHECK( 42 == t6c.GetResult() );

    auto t7 = MakeTask( [&] { ++ count; } );
    auto t7c = t7.Then( "Marisa", [] { return std::string( "Spark" ); } );

    CHECK( "Marisa" == t7c.Name() );

    AsyncSubmit( t7 );
    t7c.Wait();

    CHECK( "Spark" == t7c.GetResult() );
}


TEST( TaskContinuationWithAnotherExecutor )
{
    TaskPoller poller;

    Int value1 = 0;

    auto task1 = MakeTask( [] { return 42; });
    auto then1 = task1.Then( poller,
    [&] ( Int v )
    {
        value1 = v;
    });
    auto fence1 = task1.Then( [] {} );

    poller.PollOne();

    AsyncSubmit( task1 );
    fence1.Wait();

    CHECK( false == then1.IsDone() );

    poller.PollOne();

    CHECK( true == then1.IsDone() );
    CHECK( 42 == value1 );


    /// Without result ///

    Bool flag2 = false;

    auto task2 = MakeTask( [] {} );
    auto then2 = task2.Then( poller,
    [&]
    {
        flag2 = true;
    });
    auto fence2 = task2.Then( [] {} );

    poller.PollOne();

    AsyncSubmit( task2 );
    fence2.Wait();

    CHECK( false == then2.IsDone() );

    poller.PollOne();

    CHECK( true == then2.IsDone() );
    CHECK( true == flag2 );

}


} // SUITE Task

} // namespace Caramel
