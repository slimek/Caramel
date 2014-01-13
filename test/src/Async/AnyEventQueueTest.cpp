// Caramel C++ Library Test - Async - Any Event Queue Test

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEventQueue.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( AnyEventQueueSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Queue Test
//

TEST( AnyEventQueueTest )
{
    AnyEventQueue equeue;

    auto port1 = equeue.Register( "Port1", 10, 19 );
    
    port1.PushEvent( 10, 42 );
    port1.PushEvent( 11, "Alice" );

    AnyEvent evt;
    CHECK( true == equeue.TryPop( evt ));
    CHECK( 10 == evt.Id() );
    CHECK( 42 == evt.Value< Int >() );

    CHECK( true == equeue.TryPop( evt ));
    CHECK( 11 == evt.Id() );
    CHECK( "Alice" == evt.Value< std::string >() );

    CHECK( false == equeue.TryPop( evt ));
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE AnyEventQueueSuite

} // namespace Caramel
