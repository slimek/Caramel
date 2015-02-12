// Caramel C++ Library Test - Async - Any Event Handler Suite

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEventHandler.h>
#include <Caramel/Async/AnyEventQueue.h>
#include <Caramel/Async/AnyEventSlot.h>


namespace Caramel
{

SUITE( AnyEventHandlerSuite )
{

TEST( AnyEventHandlerTrivalTest )
{
    AnyEventSlot slot;

    AnyEventHandler def;
    AnyEventHandler null( nullptr );
    AnyEventHandler empty = AnyEventHandler::Empty();
    AnyEventHandler func( [] ( const AnyEvent& e ) {} );
    AnyEventHandler signal( slot );

    CHECK( ! def );
    CHECK( ! null );
    CHECK( empty );
    CHECK( func );
    CHECK( signal );

    AnyEvent event;

    CHECK_THROW( null( event ), std::bad_function_call );
    
    empty( event );  // An empty handler just do nothing.
}


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

    CHECK( ! slot );

    handler( AnyEvent( 2, 42 ));

    CHECK( slot );
    CHECK( 2  == slot.Id() );
    CHECK( 42 == slot.Value< Int >() );


    // Reset the slot should break the linking

    slot.Reset();

    handler( AnyEvent( 7, "Alice" ));

    CHECK( ! slot );
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


AnyEventHandler WrapHandler( AnyEventHandler handler )
{
    return handler;
}


TEST( AnyEventHandlerConversionTest )
{
    AnyEvent event;

    auto handler1 = WrapHandler(
    [&] ( const AnyEvent& e )
    {
        event = e;
    });

    handler1( AnyEvent( 2, 42 ));

    CHECK( 2  == event.Id() );
    CHECK( 42 == event.Value< Int >() );

    AnyEventQueue equeue;

    auto handler2 = WrapHandler( equeue );

    handler2( AnyEvent( 7, "Alice" ));

    CHECK( true == equeue.TryPop( event ));
    CHECK( 7       == event.Id() );
    CHECK( "Alice" == event.Value< std::string >() );
}


TEST( AnyEventHandlerAssignmentTest )
{
    AnyEventQueue queue;
    AnyEventSlot slot;

    AnyEventHandler h1( queue );
    AnyEventHandler h2( slot );
    AnyEvent event;

    h1 = h2;

    h1( AnyEvent( 514, "Koishi" ));

    CHECK( false == queue.TryPop( event ));
    CHECK( slot );
    CHECK( 514 == slot.Id() );
    CHECK( "Koishi" == slot.Value< std::string >() );

    slot.Take();  // Take out the event.
                  // Don't call Reset() or you will unlink from the handlers.

    // Self-assign
    h2 = h2;

    h2( AnyEvent( 501, "Satori" ));

    CHECK( slot );
    CHECK( 501 == slot.Id() );
    CHECK( "Satori" == slot.Value< std::string >() );
}


} // SUITE AnyEventHandlerSuite

} // namespace Caramel
