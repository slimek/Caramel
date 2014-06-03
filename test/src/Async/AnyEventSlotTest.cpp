// Caramel C++ Library Test - Async - Any Event Slot Test

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEventDispatcher.h>
#include <Caramel/Async/AnyEventSlot.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( AnyEventSlotSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Slot Test
//

TEST( AnyEventSlotTrivialTest )
{
    AnyEventSlot slot;

    CHECK( false == slot );
    CHECK( false == slot.IsValid() );
    CHECK( true  == slot.IsEmpty() );

    CHECK_THROW( slot.Id(), Caramel::Exception );
    CHECK_THROW( slot.Value< Int >(), Caramel::Exception );
}


TEST( AnyEventSlotTest )
{
    AnyEventDispatcher disp( 1, 10 );
    AnyEventSlot slot;

    disp.LinkTarget( slot );
    disp.DispatchEvent( 2, 42 );

    CHECK( true  == slot );
    CHECK( true  == slot.IsValid() );
    CHECK( false == slot.IsEmpty() );
    CHECK( 2     == slot.Id() );
    CHECK( 42    == slot.Value< Int >() );

    // After the first event, other events would be discarded.

    disp.DispatchEvent( 4, 51 );
    CHECK( 2 == slot.Id() );

    // Reset the slot

    slot.Reset();
    CHECK( false == slot );

    disp.DispatchEvent( 5, "Reimu" );
    CHECK( false == slot );

    // Link again

    disp.LinkTarget( slot );
    disp.DispatchEvent( 7, "Alice" );

    CHECK( true    == slot );
    CHECK( 7       == slot.Id() );
    CHECK( "Alice" == slot.Value< std::string >() );


    // Take the Event from the Slot

    auto event = slot.Take();

    CHECK( false   == slot );
    CHECK( 7       == event.Id() );
    CHECK( "Alice" == event.Value< std::string >() );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE AnyEventSlotSuite

} // namespace Caramel
