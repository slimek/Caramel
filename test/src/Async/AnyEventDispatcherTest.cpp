// Caramel C++ Library Test - Async - Any Event Dispatcher Test

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEventDispatcher.h>
#include <Caramel/Async/AnyEventQueue.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( AnyEventDispatcherSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Dispatcher Test
//

TEST( AnyEventDispatcherTrivialTest )
{
    AnyEventDispatcher disp( 1, 4 );

    // Nothing happen
    disp.Dispatch( AnyEvent( 1 ));
    disp.DispatchEvent( 2 );
    disp.DispatchEvent( 3, 42 );
    disp.DispatchEvent( 4, "Alice" );
}


TEST( AnyEventDispatcherToQueueTest )
{
    AnyEventDispatcher disp( 1, 100 );

    AnyEventQueue dq1;
    AnyEventQueue dq2;

    AnyEvent value;

    disp.LinkTarget( dq1 );
    disp.LinkTarget( dq2 );

    CHECK( false == dq1.TryPop( value ));
    CHECK( false == dq2.TryPop( value ));

    disp.DispatchEvent( 42 );

    CHECK( true == dq1.TryPop( value ));
    CHECK( 42 == value.Id() );
    CHECK( true == dq2.TryPop( value ));
    CHECK( 42 == value.Id() );

    disp.UnlinkTarget( dq1 );

    disp.DispatchEvent( 51 );

    CHECK( false == dq1.TryPop( value ));
    CHECK( true == dq2.TryPop( value ));
    CHECK( 51 == value.Id() );

    /// Automatically remove target ///

    std::shared_ptr< Detail::AnyEventQueueImpl > dq3impl;

    {
        AnyEventQueue dq3;
        dq3impl = std::static_pointer_cast< Detail::AnyEventQueueImpl >( dq3.GetImpl() );

        disp.LinkTarget( dq3 );

        disp.DispatchEvent( 72 );

        CHECK( true == dq3.TryPop( value ));
        CHECK( 72 == value.Id() );
        CHECK( true == dq2.TryPop( value ));
        CHECK( 72 == value.Id() );

        CHECK( false == dq3.TryPop( value ));
    }

    disp.DispatchEvent( 81 );

    CHECK( false == dq3impl->TryPop( value ));

    CHECK( true == dq2.TryPop( value ));
    CHECK( 81 == value.Id() );
}


TEST( AnyEventDispatcherToDispatcherTest )
{
    AnyEventDispatcher disp1( 1, 100 );
    AnyEventDispatcher disp2( 101, 200 );
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
        AnyEventDispatcher disp3( 201, 300 );

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
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE AnyEventDispatcherSuite

} // namespace Caramel
