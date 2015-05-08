// Caramel C++ Library Test - Async - Any Event Task Suite

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEventQueue.h>
#include <Caramel/Async/AnyEventReactor.h>
#include <Caramel/Async/AnyEventTask.h>
#include <Caramel/Task/StdAsync.h>


namespace Caramel
{

SUITE( AnyEventTask )
{

static AnyEventTask TaskYukari()
{
    auto task = MakeTask( [] { return AnyEvent( 22, "Yukari" ); });
    StdAsync::Submit( task );
    return task;
}


TEST( AnyEventTask )
{
    /// Get the result directly ///

    AnyEventTask t1 = MakeTask( [] { return AnyEvent( 7, "Alice" ); } );
    t1.Run();

    auto e1 = t1.GetResult();
    CHECK( 7       == e1.Id() );
    CHECK( "Alice" == e1.Value< std::string >() );

    CHECK( 7       == t1.Id() );
    CHECK( "Alice" == t1.Value< std::string >() );


    /// Get the result in a handler - Access events by task ///

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


    /// Get the result in a handler - Access events by lambda parameter ///

    Int id3 = 0;
    std::string value3;

    auto t3 = TaskYukari().Then(
    [&] ( const AnyEvent& event )
    {
        id3 = event.Id();
        value3 = event.Value< std::string >();
    });

    t3.Wait();

    CHECK( 22       == id3 );
    CHECK( "Yukari" == value3 );


    /// Send the result into a Target ///

    AnyEventQueue queue;

    AnyEventTask t4 = MakeTask( [] { return AnyEvent( 8, "Marisa" ); } );
    t4.Link( queue );

    t4.Run();

    AnyEvent e4;
    CHECK( queue.TryPop( e4 ));
    CHECK( 8 == e4.Id() );
    CHECK( "Marisa" == e4.Value< std::string >() );


    /// Send the result into a Reactor ///

    AnyEventReactor reactor;

    AnyEventTask t5 = MakeTask( [] { return AnyEvent( 51, "Nitori" ); });

    AnyEvent e5;    
    
    t5.Link( reactor.Receive(
    [&] ( const AnyEvent& event )
    {
        e5 = event;
    }));

    t5.Run();
    reactor.PollOne();

    CHECK( 51 == e5.Id() );
    CHECK( "Nitori" == e5.Value< std::string >() );
}

} // SUITE AnyEventTask

} // namespace Caramel
