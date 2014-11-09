// Caramel C++ Library Test - Async - Any Event Poller Suite

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEventDispatcher.h>
#include <Caramel/Async/AnyEventHandler.h>
#include <Caramel/Async/AnyEventPoller.h>
#include <Caramel/Task/StdAsync.h>
#include <Caramel/Thread/ThisThread.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( AnyEventPollerSuite )
{

TEST( AnyEventPollerTest )
{
    AnyEventPoller poller;
    AnyEvent buffer;

    auto threadId = ThisThread::GetId();

    auto source = poller.Receive(
    [&] ( const AnyEvent& event )
    {
        buffer = event;

        CHECK( threadId == ThisThread::GetId() );
    });

    source.AsHandler()( AnyEvent( 7, "Alice" ));

    CHECK( buffer.IsValid() == false );

    poller.PollOne();

    CHECK( buffer.IsValid() == true );
    CHECK( buffer.Id() == 7 );
    CHECK( buffer.Value< std::string >() == "Alice" );


    /// Link to a Dispatcher ///

    AnyEventDispatcher disp;

    disp.LinkTarget( source );
    disp.DispatchEvent( 9, "Cirno" );

    poller.PollOne();

    CHECK( buffer.Id() == 9 );
    CHECK( buffer.Value< std::string >() == "Cirno" );


    /// Passed to a Handler ///

    AnyEventHandler handler( source );

    handler( AnyEvent( 514, "Koishi" ));

    poller.PollOne();

    CHECK( buffer.Id() == 514 );
    CHECK( buffer.Value< std::string >() == "Koishi" );


    /// Passed to Another Thread ///

    auto task = MakeTask( "EventPoller",
    [=]
    {
        source.AsHandler()( AnyEvent( 42, "Yukari" ));
    });

    StdAsync async;
    async.Submit( task );

    task.Wait();

    poller.PollOne();

    CHECK( buffer.Id() == 42 );
    CHECK( buffer.Value< std::string >() == "Yukari" );


    //
    // Reset the Source
    // - Unlink from dispatchers, but can still emit event to poller.
    //

    // Clear the buffer
    buffer = AnyEvent();
    CHECK( buffer.IsValid() == false );

    source.Reset();

    disp.DispatchEvent( 3, "Utsuho" );

    poller.PollOne();

    CHECK( buffer.IsValid() == false );

    source.AsHandler()( AnyEvent( 5, "Kaguya" ));

    poller.PollOne();

    CHECK( buffer.Id() == 5 );
    CHECK( buffer.Value< std::string >() == "Kaguya" );


    //
    // Reset the Poller
    // - Unlink from all sources, and clear the event queue.
    //

    // Clear the buffer
    buffer = AnyEvent();
    CHECK( buffer.IsValid() == false );

    // Put an event into poller, but doesn't consume it.
    source.AsHandler()( AnyEvent( 8, "Eirin" ));

    poller.Reset();

    // After reset, the previous events are discarded.
    poller.PollOne();
    CHECK( buffer.IsValid() == false );

    // Sources are also unlinked from poller.
    source.AsHandler()( AnyEvent( 6, "Nitori" ));

    poller.PollOne();
    CHECK( buffer.IsValid() == false );
}


} // SUITE AnyEventPollerSuite

} // namespace Caramel
