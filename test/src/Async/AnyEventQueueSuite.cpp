// Caramel C++ Library Test - Async - Any Event Queue Suite

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEventDispatcher.h>
#include <Caramel/Async/AnyEventHandler.h>
#include <Caramel/Async/AnyEventQueue.h>
#include <Caramel/Task/StdAsync.h>


namespace Caramel
{

SUITE( AnyEventQueue )
{

TEST( AnyEventQueue )
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


TEST( AnyEventQueueUnlink )
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


TEST( AnyEventQueueProxy )
{
    AnyEventQueue queue;
    AnyEvent event;

    auto proxy1 = queue.Proxy();
    proxy1.PushEvent( 42 );

    CHECK( true == queue.TryPop( event ));
    CHECK( 42 == event.Id() );

    queue.Reset();  // Unlink queue from proxy1.

    proxy1.PushEvent( 51 );

    CHECK( false == queue.TryPop( event ));

    
    /// Capture proxy to a lambda ///

    auto proxy2 = queue.Proxy();

    auto task = MakeTask( "QueueProxy",
    [=]
    {
        proxy2.PushEvent( 8, "Marisa" );
    });

    StdAsync::Submit( task );
    task.Wait();

    CHECK( true == queue.TryPop( event ));
    CHECK( 8 == event.Id() );
    CHECK( "Marisa" == event.Value< std::string >() );


    /// Put into an AnyEventHandler ///

    AnyEventHandler handler( proxy2 );
    handler( AnyEvent( 514, "Koishi" ));

    CHECK( true == queue.TryPop( event ));
    CHECK( 514 == event.Id() );
    CHECK( "Koishi" == event.Value< std::string >() );
}


} // SUITE AnyEventQueue

} // namespace Caramel
