// Caramel C++ Library Test - Async - Any Event Reactor Suite

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEventDispatcher.h>
#include <Caramel/Async/AnyEventHandler.h>
#include <Caramel/Async/AnyEventReactor.h>
#include <Caramel/Task/StdAsync.h>
#include <Caramel/Thread/ThisThread.h>


namespace Caramel
{

SUITE( AnyEventReactorSuite )
{

TEST( AnyEventReactorTest )
{
    AnyEventReactor reactor;
    AnyEvent buffer;

    auto threadId = ThisThread::GetId();

    auto source = reactor.Receive(
    [&] ( const AnyEvent& event )
    {
        buffer = event;

        CHECK( threadId == ThisThread::GetId() );
    });

    source.AsHandler()( AnyEvent( 7, "Alice" ));

    CHECK( buffer.IsValid() == false );

    reactor.PollOne();

    CHECK( buffer.IsValid() == true );
    CHECK( buffer.Id() == 7 );
    CHECK( buffer.Value< std::string >() == "Alice" );


    /// Link to a Dispatcher ///

    AnyEventDispatcher disp;

    disp.LinkTarget( source );
    disp.DispatchEvent( 9, "Cirno" );

    reactor.PollOne();

    CHECK( buffer.Id() == 9 );
    CHECK( buffer.Value< std::string >() == "Cirno" );


    /// Passed to a Handler ///

    AnyEventHandler handler( source );

    handler( AnyEvent( 514, "Koishi" ));

    reactor.PollOne();

    CHECK( buffer.Id() == 514 );
    CHECK( buffer.Value< std::string >() == "Koishi" );


    /// Passed to Another Thread ///

    auto task = MakeTask( "Eventreactor",
    [=]
    {
        source.AsHandler()( AnyEvent( 42, "Yukari" ));
    });

    StdAsync::Submit( task );

    task.Wait();

    reactor.PollOne();

    CHECK( buffer.Id() == 42 );
    CHECK( buffer.Value< std::string >() == "Yukari" );


    //
    // Reset the Source
    // - Unlink from dispatchers, but can still emit event to reactor.
    //

    // Clear the buffer
    buffer = AnyEvent();
    CHECK( buffer.IsValid() == false );

    source.Reset();

    disp.DispatchEvent( 3, "Utsuho" );

    reactor.PollOne();

    CHECK( buffer.IsValid() == false );

    source.AsHandler()( AnyEvent( 5, "Kaguya" ));

    reactor.PollOne();

    CHECK( buffer.Id() == 5 );
    CHECK( buffer.Value< std::string >() == "Kaguya" );


    //
    // Reset the reactor
    // - Unlink from all sources, and clear the event queue.
    //

    // Clear the buffer
    buffer = AnyEvent();
    CHECK( buffer.IsValid() == false );

    // Put an event into reactor, but doesn't consume it.
    source.AsHandler()( AnyEvent( 8, "Eirin" ));

    reactor.Reset();

    // After reset, the previous events are discarded.
    reactor.PollOne();
    CHECK( buffer.IsValid() == false );

    // Sources are also unlinked from reactor.
    source.AsHandler()( AnyEvent( 6, "Nitori" ));

    reactor.PollOne();
    CHECK( buffer.IsValid() == false );
}


} // SUITE AnyEventReactorSuite

} // namespace Caramel
