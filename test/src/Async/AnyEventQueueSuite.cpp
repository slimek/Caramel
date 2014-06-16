// Caramel C++ Library Test - Async - Any Event Queue Suite

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEventDispatcher.h>
#include <Caramel/Async/AnyEventQueue.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( AnyEventQueueSuite )
{

TEST( AnyEventQueueTest )
{
    AnyEventQueue equeue;

    equeue.PushEvent( 10, 42 );
    equeue.PushEvent( 11, "Alice" );

    AnyEvent evt;
    CHECK( true == equeue.TryPop( evt ));
    CHECK( 10 == evt.Id() );
    CHECK( 42 == evt.Value< Int >() );

    CHECK( true == equeue.TryPop( evt ));
    CHECK( 11 == evt.Id() );
    CHECK( "Alice" == evt.Value< std::string >() );

    CHECK( false == equeue.TryPop( evt ));

    
    /// Push AnyEvent ///

    AnyEvent reimu( 13, "Reimu" );

    equeue.Push( AnyEvent( 12, 125 ));
    equeue.Push( reimu );

    CHECK( true == equeue.TryPop( evt ));
    CHECK( 12 == evt.Id() );
    CHECK( 125 == evt.Value< Int >() );

    CHECK( true == equeue.TryPop( evt ));
    CHECK( 13 == evt.Id() );
    CHECK( "Reimu" == evt.Value< std::string >() );

    CHECK( false == equeue.TryPop( evt ));


    /// Push lvalue Any ///

    const Any marisa( "Marisa" );

    equeue.PushEvent( 14, marisa );

    CHECK( true == equeue.TryPop( evt ));
    CHECK( 14 == evt.Id() );
    CHECK( "Marisa" == evt.Value< std::string >() );

    CHECK( false == equeue.TryPop( evt ));
}


TEST( AnyEventQueueUnlinkTest )
{
    AnyEventDispatcher edisp;
    AnyEventQueue equeue;
    AnyEvent event;

    edisp.LinkTarget( equeue );

    CHECK( 1 == edisp.GetNumTargets() );

    edisp.DispatchEvent( 42 );

    CHECK( true == equeue.TryPop( event ));
    CHECK( 42 == event.Id() );

    equeue.Reset();

    // After Reset(), the target reference in Dispatcher is marked "over-aged",
    // but not removed yet, until DispatchEvent() to update its target list.

    edisp.DispatchEvent( 51 );

    CHECK( 0 == edisp.GetNumTargets() );

    CHECK( false == equeue.TryPop( event ));

    
    // Attach to another Dispatcher

    AnyEventDispatcher edisp2;

    edisp2.LinkTarget( equeue );
    edisp2.DispatchEvent( 125 );

    CHECK( true == equeue.TryPop( event ));
    CHECK( 125  == event.Id() );


    // Attach to the first Dispatcher again

    edisp.LinkTarget( equeue );
    edisp.DispatchEvent( 19 );

    CHECK( true == equeue.TryPop( event ));
    CHECK( 19   == event.Id() );
}


} // SUITE AnyEventQueueSuite

} // namespace Caramel
