// Caramel C++ Library Test - Async - Any Event Dispatcher Suite

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEventDispatcher.h>
#include <Caramel/Async/AnyEventHandler.h>
#include <Caramel/Async/AnyEventQueue.h>
#include <Caramel/Async/AnyEventSlot.h>
#include <Caramel/Task/StdAsync.h>


namespace Caramel
{

SUITE( AnyEventDispatcherSuite )
{

TEST( AnyEventDispatcherTrivialTest )
{
    AnyEventDispatcher disp;

    // Nothing happen
    disp.Dispatch( AnyEvent( 1 ));
    disp.DispatchEvent( 2 );
    disp.DispatchEvent( 3, 42 );
    disp.DispatchEvent( 4, "Alice" );
}


TEST( AnyEventDispatcherToQueueTest )
{
    AnyEventDispatcher disp;

    AnyEventQueue dq1;
    AnyEventQueue dq2;

    AnyEvent value;

    disp.LinkTarget( dq1 );
    disp.LinkTarget( dq2 );

    CHECK( 2 == disp.GetNumTargets() );

    CHECK( false == dq1.TryPop( value ));
    CHECK( false == dq2.TryPop( value ));

    disp.DispatchEvent( 42 );

    CHECK( true == dq1.TryPop( value ));
    CHECK( 42 == value.Id() );
    CHECK( true == dq2.TryPop( value ));
    CHECK( 42 == value.Id() );

    disp.UnlinkTarget( dq1 );

    CHECK( 1 == disp.GetNumTargets() );

    disp.DispatchEvent( 51 );

    CHECK( false == dq1.TryPop( value ));
    CHECK( true == dq2.TryPop( value ));
    CHECK( 51 == value.Id() );

    /// Automatically remove target ///

    {
        AnyEventQueue dq3;

        disp.LinkTarget( dq3 );

        disp.DispatchEvent( 72 );

        CHECK( true == dq3.TryPop( value ));
        CHECK( 72 == value.Id() );
        CHECK( true == dq2.TryPop( value ));
        CHECK( 72 == value.Id() );

        CHECK( false == dq3.TryPop( value ));
    }

    // After dq3 destroyed, the target reference in Dispatcher is marked "destroyed",
    // but not removed yet. Wait until DispatchEvent() to update its target list.

    disp.DispatchEvent( 81 );

    CHECK( 1 == disp.GetNumTargets() );

    CHECK( true == dq2.TryPop( value ));
    CHECK( 81 == value.Id() );
}


TEST( AnyEventDispatcherToDispatcherTest )
{
    AnyEventDispatcher disp1;
    AnyEventDispatcher disp2;
    AnyEventQueue dq1;
    AnyEventQueue dq3;

    AnyEvent value;

    disp1.LinkTarget( disp2 );
    disp2.LinkTarget( dq1 );

    CHECK( false == dq1.TryPop( value ));

    disp1.DispatchEvent( 42 );

    CHECK( true == dq1.TryPop( value ));
    CHECK( 42 == value.Id() );


    /// Automatically remove target ///

    {
        AnyEventDispatcher disp3;

        disp1.LinkTarget( disp3 );
        disp3.LinkTarget( dq3 );

        disp1.DispatchEvent( 72 );

        CHECK( true == dq1.TryPop( value ));
        CHECK( 72 == value.Id() );
        CHECK( true == dq3.TryPop( value ));
        CHECK( 72 == value.Id() );

        CHECK( false == dq3.TryPop( value ));
    }

    disp1.DispatchEvent( 81 );

    CHECK( false == dq3.TryPop( value ));

    CHECK( true == dq1.TryPop( value ));
    CHECK( 81 == value.Id() );

    
    // Reset 
    // If we reset disp2, it should unlink from disp1.

    disp2.Reset();

    disp1.DispatchEvent( 125 );

    CHECK( false == dq1.TryPop( value ));
}


TEST( AnyEventDispatcherProxyTest )
{
    AnyEventDispatcher disp;
    AnyEventSlot slot;

    disp.LinkTarget( slot );

    CHECK( ! slot );

    auto proxy1 = disp.Proxy();
    proxy1.DispatchEvent( 42 );

    CHECK( slot );
    CHECK( 42 == slot.Take().Id() );

    disp.Reset();  // Unlink disp from proxy1

    proxy1.DispatchEvent( 51 );

    CHECK( ! slot );

    auto proxy2 = disp.Proxy();

    auto task = MakeTask( "DispatcherProxy",
    [=]
    {
        proxy2.DispatchEvent( 7, "Alice" );
    });

    StdAsync().Submit( task );
    task.Wait();

    CHECK( slot );

    auto event = slot.Take();
    CHECK( 7 == event.Id() );
    CHECK( "Alice" == event.Value< std::string >() );


    /// Put into an AnyEventHandler ///

    AnyEventHandler handler( proxy2 );
    handler( AnyEvent( 501, "Satori" ));

    CHECK( slot );

    event = slot.Take();
    CHECK( 501 == event.Id() );
    CHECK( "Satori" == event.Value< std::string >() );
}


} // SUITE AnyEventDispatcherSuite

} // namespace Caramel
