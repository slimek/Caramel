// Caramel C++ Library Test - Async - Any Event Suite

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEvent.h>
#include <Caramel/Concurrent/Queue.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( AnyEventSuite )
{

TEST( AnyEventTest )
{
    /// Not an Event ///

    const AnyEvent evt0;

    CHECK( false == evt0.IsValid() );
    CHECK( false == evt0.HasValue() );
    CHECK_THROW( evt0.Id(), Caramel::Exception );
    CHECK_THROW( evt0.Value< Int >(), Caramel::Exception );


    /// Empty Event ///

    auto evt1 = AnyEvent( 1 );

    CHECK( true  == evt1.IsValid() );
    CHECK( false == evt1.HasValue() );
    CHECK( 1 == evt1.Id() );
    CHECK_THROW( evt1.Value< Int >(), Caramel::Exception );


    /// Normal Event ///

    auto evt2 = AnyEvent( 2, "Alice" );
    auto evt3 = AnyEvent( 3, 42 );

    
    CHECK( 2 == evt2.Id() );
    CHECK( "Alice" == evt2.Value< std::string >() );
    CHECK( true == evt2.HasValue() );
    
    CHECK( 3 == evt3.Id() );
    CHECK( 42 == evt3.Value< Int >() );
    CHECK( 42 == evt3.Value< Uint >() );
    CHECK( 42 == evt3.Value< Float >() );

    // Invalid conversion
    CHECK_THROW( evt2.Value< Int >(), Caramel::Exception );
    CHECK_THROW( evt3.Value< std::string >(), Caramel::Exception );
}


enum EventId
{
    EVENT_NONE   = 0,
    EVENT_INT    = 1,
    EVENT_FLOAT  = 2,
    EVENT_STRING = 3,
    EVENT_WIDGET = 4,
    EVENT_PAIR   = 5,
};

struct Widget
{
    Int id;
    std::string name;
};

TEST( AnyEventQueueTest )
{
    Concurrent::Queue< AnyEvent > equeue;

    Widget w;
    w.id = 99;
    w.name = "Cirno";

    equeue.Push( AnyEvent( EVENT_FLOAT, 3.1416f ));
    equeue.Push( AnyEvent( EVENT_STRING, "Alice" ));
    equeue.Push( AnyEvent( EVENT_NONE ));
    equeue.Push( AnyEvent( EVENT_WIDGET, w ));
    equeue.Push( AnyEvent( EVENT_INT, 42 ));

    AnyEvent evt;
    while ( equeue.TryPop( evt ))
    {
        switch ( evt.Id() )
        {
        case EVENT_NONE:
            CHECK( false == evt.HasValue() );
            break;

        case EVENT_INT:
            CHECK( 42 == evt.Value< Int >() );
            break;

        case EVENT_FLOAT:
            CHECK( 3.1416f == evt.Value< Float >() );
            break;

        case EVENT_STRING:
            CHECK( "Alice" == evt.Value< std::string >() );
            break;

        case EVENT_WIDGET:
        {
            const auto w = evt.Value< Widget >();
            CHECK( 99 == w.id );
            CHECK( "Cirno" == w.name );
            break;
        }

        default:
            CARAMEL_NOT_REACHED();
        }
    }
}


} // SUITE AnyEventSuite

} // namespace Caramel
