// Caramel C++ Library Test - Async - Any Event Task Suite

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEventQueue.h>
#include <Caramel/Async/AnyEventTask.h>


namespace Caramel
{

SUITE( AnyEventTaskSuite )
{

TEST( AnyEventTaskTest )
{
    /// Get the result directly ///

    AnyEventTask t1 = MakeTask( [] { return AnyEvent( 7, "Alice" ); } );
    t1.Run();

    auto e1 = t1.GetResult();
    CHECK( 7       == e1.Id() );
    CHECK( "Alice" == e1.Value< std::string >() );

    CHECK( 7       == t1.Id() );
    CHECK( "Alice" == t1.Value< std::string >() );


    /// Get the result in a handler ///

    Int id2 = 0;
    std::string value2;

    AnyEventTask t2 = MakeTask( [] { return AnyEvent( 2, "Reimu" ); } );
    t2.Then(
    [&] ()
    {
        id2 = t2.Id();
        value2 = t2.Value< std::string >();
    });

    t2.Run();

    CHECK( 2       == id2 );
    CHECK( "Reimu" == value2 );


    /// Send the result into a Target ///

    AnyEventQueue queue;

    AnyEventTask t3 = MakeTask( [] { return AnyEvent( 8, "Marisa" ); } );
    t3.Link( queue );

    t3.Run();

    AnyEvent e3;
    CHECK( queue.TryPop( e3 ));
    CHECK( 8 == e3.Id() );
    CHECK( "Marisa" == e3.Value< std::string >() );
}

} // SUITE AnyEventTaskSuite

} // namespace Caramel
