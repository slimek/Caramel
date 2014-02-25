// Caramel C++ Library Test - Task - Task Test

#include "CaramelTestPch.h"

#include <Caramel/Error/CatchException.h>
#include <Caramel/Task/StdAsync.h>
#include <Caramel/Task/Task.h>
#include <UnitTest++/UnitTest++.h>
#include <functional>


namespace Caramel
{

SUITE( TaskSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Test
//

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


///////////////////////////////////////////////////////////////////////////////

} // SUITE TaskSuite

} // namespace Caramel
