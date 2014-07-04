// Caramel C++ Library Test - Task - Task Suite

#include "CaramelTestPch.h"

#include "Utils/StdVectorUtils.h"
#include <Caramel/Error/CatchException.h>
#include <Caramel/Task/StdAsync.h>
#include <Caramel/Task/Task.h>
#include <Caramel/Task/WorkerThread.h>
#include <Caramel/Thread/ThisThread.h>
#include <UnitTest++/UnitTest++.h>
#include <vector>
#include <functional>


namespace Caramel
{

SUITE( TaskSuite )
{

static Bool s_calledFoo = false;

void Foo() { s_calledFoo = true; }


TEST( TaskNotTaskTest )
{
    Task< void > t0;

    CHECK( false        == t0.IsValid() );
    CHECK( "Not-a-task" == t0.Name() );
    CHECK( false        == t0.HasDelay() );
    CHECK( Ticks( 0 )   == t0.GetDelayDuration() );

    CHECK_THROW( t0.DelayFor( Ticks( 100 )), Caramel::Exception );
    CHECK_THROW( t0.Run(), Caramel::Exception );


    Task< Int > t1;

    CHECK( false        == t1.IsValid() );
    CHECK( "Not-a-task" == t1.Name() );
    CHECK( false        == t1.HasDelay() );
    CHECK( Ticks( 0 )   == t1.GetDelayDuration() );

    CHECK_THROW( t1.DelayFor( Ticks( 100 )), Caramel::Exception );
    CHECK_THROW( t1.Run(), Caramel::Exception );
}


TEST( TaskTrivialTest )
{
    auto t1 = MakeTask( "Foo", &Foo );

    CHECK( true       == t1.IsValid() );
    CHECK( "Foo"      == t1.Name() );
    CHECK( false      == t1.HasDelay() );
    CHECK( Ticks( 0 ) == t1.GetDelayDuration() );

    t1.DelayFor( Ticks( 100 ));

    CHECK( true         == t1.HasDelay() );
    CHECK( Ticks( 100 ) == t1.GetDelayDuration() );
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


TEST( TaskMemberFunctionTest )
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


TEST( TaskOfBindMacroTest )
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


TEST( TaskWithResultTest )
{
    auto itask = MakeTask( "IntTask", [] { return 42; } );

    itask.Run();
    CHECK( 42 == itask.GetResult() );

    auto stask = MakeTask( "StrTask", [] { return std::string( "Alice" ); } );

    stask.Run();
    CHECK( "Alice" == stask.GetResult() );
}


TEST( TaskWithExceptionTest )
{
    StdAsync async;
    std::string what;


    /// Exception in Wait() ///

    auto task1 = MakeTask( "BadTask1", [] { throw std::exception( "bad1" ); } );
    async.Submit( task1 );

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

    Task< Int > task2 = MakeTask( "BadTask2", [] { throw std::exception( "bad2" ); return 42; } );
    async.Submit( task2 );

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


TEST( TaskWaitOrCatchTest )
{
    StdAsync async;
    std::string what;

    auto task1 = MakeTask( "Task1", [] {} );
    async.Submit( task1 );


    /// Ran to Completing ///

    const auto result1 = task1.Catch();

    CHECK( TASK_STATE_RAN_TO_COMP == result1.doneState );
    CHECK( ! result1.anyFailure );
    CHECK( ! result1.exception );


    /// Fault with std::exception ///

    auto task2 = MakeTask( "Task2", [] { throw std::exception( "bad" ); } );
    async.Submit( task2 );

    const auto result2 = task2.Catch();

    CHECK( TASK_STATE_FAULTED == result2.doneState );
    CHECK( ! result2.anyFailure );
    CHECK( result2.exception );

    CHECK( nullptr == result2.anyFailure.operator->() );


    /// Fault with AnyFailure ///

    auto task3 = MakeTask( "Task3", [] { throw AnyFailure( 42, "Cirno" ); } );
    async.Submit( task3 );

    const auto result3 = task3.Catch();

    CHECK( TASK_STATE_FAULTED == result3.doneState );
    CHECK( result3.anyFailure );
    CHECK( result3.exception );

    CHECK( 42      == result3.anyFailure->Id() );
    CHECK( "Cirno" == result3.anyFailure->Value< std::string >() );
}


TEST( TaskThenSuite )
{
    StdAsync async;
    Int count1 = 0;

    auto task1 = MakeTask( "Task1", [&] { ++ count1; } );
    auto task1c = task1.Then( "Task1+Continue", [&] { ++ count1; } );

    CHECK( "Task1+Continue" == task1c.Name() );

    async.Submit( task1 );
    task1c.Wait();

    CHECK( 2 == count1 );
    

    /// Continuation Task uses a default name ///

    Int count2 = 0;

    auto task2 = MakeTask( "Task2", [&] { ++ count2; } );
    auto task2c = task2.Then( [&] { ++ count2; } );

    CHECK( "Task2-Then" == task2c.Name() );

    async.Submit( task2 );
    task2c.Wait();

    CHECK( 2 == count2 );


    /// Continuatioin Task with return values ///

    auto task3 = MakeTask( "Task3", [] {} );
    auto task3c = task3.Then( [] { return 42; } );
    auto task3d = task3c.Then( [] { return std::string( "Cirno" ); } );

    CHECK( "Task3-Then-Then" == task3d.Name() );

    async.Submit( task3 );
    task3d.Wait();

    CHECK( 42 == task3c.GetResult() );
    CHECK( "Cirno" == task3d.GetResult() );
}


TEST( TaskContinueImmediatelyTest )
{
    /// The First Continuation should be executed immediately ///

    // Expected execute order:
    //      task  (Submit)
    //   >> taskc (Continue)
    //   >> taske (Submit)
    //
    //   Because task delayed for 100 ms, submit of taske is faster than continue of task4c.
    //   But task4c should run before task4e.

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


} // SUITE TaskSuite

} // namespace Caramel
