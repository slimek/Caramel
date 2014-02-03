// Caramel C++ Library Test - Task - Task Test

#include "CaramelTestPch.h"

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
    Task t0;

    CHECK( false        == t0.IsValid() );
    CHECK( "Not-a-task" == t0.Name() );
    CHECK( false        == t0.HasDelay() );
    CHECK( Ticks( 0 )   == t0.GetDelayDuration() );

    CHECK_THROW( t0.DelayFor( Ticks( 100 )), Caramel::Exception );
    CHECK_THROW( t0.Run(), Caramel::Exception );
}


TEST( TaskTrivialTest )
{
    Task t1( "Foo", &Foo );

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

    Task t2( "Widget::Bar", std::bind( &Widget::Bar, &w ));
    Task t3( "Widget::Bar", [&] { w.Bar(); });

    std::shared_ptr< Widget > pw( new Widget );

    Task t4( "Widget::Bar", std::bind( &Widget::Bar, pw ));
    Task t5( "Widget::Bar", [=] { pw->Bar(); });
}


TEST( TaskOfBindMacroTest )
{
    /// Member Functions ///

    Widget w;

    Task bar = CARAMEL_TASK_OF_BIND( Widget::Bar, &w );

    CHECK( "Widget::Bar" == bar.Name() );

    bar.Run();

    CHECK( true == w.IsRanBar() );


    /// Stand-alone Functions ///

    s_calledFoo = false;

    Task foo = CARAMEL_TASK_OF_BIND( Foo );  // No arguments is Ok!

    CHECK( "Foo" == foo.Name() );

    foo.Run();

    CHECK( true == s_calledFoo );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE TaskSuite

} // namespace Caramel
