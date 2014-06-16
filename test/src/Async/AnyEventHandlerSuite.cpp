// Caramel C++ Library Test - Async - Any Event Handler Suite

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEventHandler.h>
#include <Caramel/Async/AnyEventQueue.h>
#include <Caramel/Async/AnyEventSlot.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( AnyEventHandlerSuite )
{

TEST( AnyEventHandlerFromLambdaTest )
{
    AnyEvent event;

    AnyEventHandler handler( [&] ( const AnyEvent& e ) { event = e; } );

    handler( AnyEvent( 2, 42 ));

    CHECK( 2  == event.Id() );
    CHECK( 42 == event.Value< Int >() );
}


TEST( AnyEventHandlerFromSlotTest )
{
    AnyEventSlot slot;

    AnyEventHandler handler( slot );

    CHECK( false == slot );

    handler( AnyEvent( 2, 42 ));

    CHECK( true == slot );
    CHECK( 2  == slot.Id() );
    CHECK( 42 == slot.Value< Int >() );


    // Reset the slot should break the linking

    slot.Reset();

    handler( AnyEvent( 7, "Alice" ));

    CHECK( false == slot );
}


TEST( AnyEventHandlerFromQueueTest )
{
    AnyEvent event;
    AnyEventQueue equeue;

    AnyEventHandler handler( equeue );

    CHECK( false == equeue.TryPop( event ));

    handler( AnyEvent( 7, "Alice" ));

    CHECK( true == equeue.TryPop( event ));
    CHECK( 7 == event.Id() );
    CHECK( "Alice" == event.Value< std::string >() );
    
    CHECK( false == equeue.TryPop( event ));


    // Reset the queue should break the linking

    equeue.Reset();

    handler( AnyEvent( 2, 42 ));

    CHECK( false == equeue.TryPop( event ));
}


} // SUITE AnyEventHandlerSuite

} // namespace Caramel
