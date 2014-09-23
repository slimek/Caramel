// Caramel C++ Library Test - Async - Any Event Slot Suite

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEventDispatcher.h>
#include <Caramel/Async/AnyEventSlot.h>
#include <UnitTest++/UnitTest++.h>
#include <functional>


namespace Caramel
{

SUITE( AnyEventSlotSuite )
{

TEST( AnyEventSlotTrivialTest )
{
    AnyEventSlot slot;

    CHECK( ! slot );
    CHECK( false == slot.IsValid() );
    CHECK( true  == slot.IsEmpty() );

    CHECK_THROW( slot.Id(), Caramel::Exception );
    CHECK_THROW( slot.Value< Int >(), Caramel::Exception );
}


TEST( AnyEventSlotTest )
{
    AnyEventDispatcher disp;
    AnyEventSlot slot;

    disp.LinkTarget( slot );
    disp.DispatchEvent( 2, 42 );

    CHECK( slot );
    CHECK( true  == slot.IsValid() );
    CHECK( false == slot.IsEmpty() );
    CHECK( 2     == slot.Id() );
    CHECK( 42    == slot.Value< Int >() );

    // After the first event, other events would be discarded.

    disp.DispatchEvent( 4, 51 );
    CHECK( 2 == slot.Id() );

    
    // Reset the slot
    // - It would unlink from all sources automatically.

    slot.Reset();
    CHECK( ! slot );

    disp.DispatchEvent( 5, "Reimu" );
    CHECK( ! slot );

    
    // Link again

    disp.LinkTarget( slot );
    disp.DispatchEvent( 7, "Alice" );

    CHECK( slot );
    CHECK( 7       == slot.Id() );
    CHECK( "Alice" == slot.Value< std::string >() );


    // Take the Event from the Slot

    auto event = slot.Take();

    CHECK( ! slot );
    CHECK( 7       == event.Id() );
    CHECK( "Alice" == event.Value< std::string >() );


    // Events without value

    disp.DispatchEvent( 42 );

    CHECK( slot );
    CHECK( 42 == slot.Id() );
    CHECK_THROW( slot.Value< Int >(), Caramel::Exception );

    auto event2 = slot.Take();

    CHECK( ! slot );
    CHECK( 42 == event2.Id() );
}


} // SUITE AnyEventSlotSuite

} // namespace Caramel
