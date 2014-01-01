// Caramel C++ Library Test - Task - Task Test

#include "CaramelTestPch.h"

#include <Caramel/Task/Strand.h>
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

void Foo() {}

static Strand s_strand;


TEST( TaskNotTaskTest )
{
    Task t0;

    CHECK( false        == t0.IsValid() );
    CHECK( "Not-a-task" == t0.Name() );
    CHECK( false        == t0.HasDelay() );
    CHECK( Ticks( 0 )   == t0.GetDelayDuration() );
    CHECK( false        == t0.HasStrand() );

    CHECK_THROW( t0.DelayFor( Ticks( 100 )), Caramel::Exception );
    CHECK_THROW( t0.Schedule( s_strand ), Caramel::Exception );
    CHECK_THROW( t0.Run(), Caramel::Exception );
}


TEST( TaskTrivialTest )
{
    Task t1( "Foo", &Foo );

    CHECK( true       == t1.IsValid() );
    CHECK( "Foo"      == t1.Name() );
    CHECK( false      == t1.HasDelay() );
    CHECK( Ticks( 0 ) == t1.GetDelayDuration() );
    CHECK( false      == t1.HasStrand() );

    t1.DelayFor( Ticks( 100 ));

    CHECK( true         == t1.HasDelay() );
    CHECK( Ticks( 100 ) == t1.GetDelayDuration() );
}


class Widget
{
public:
    void Bar() {}
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


///////////////////////////////////////////////////////////////////////////////

} // SUITE TaskSuite

} // namespace Caramel
