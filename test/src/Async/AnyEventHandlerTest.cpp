// Caramel C++ Library Test - Async - Any Event Handler Test

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEventDispatcher.h>
#include <Caramel/Async/AnyEventHandler.h>
#include <Caramel/Task/StdAsync.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( AnyEventHandlerSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Handler Test
//

TEST( AnyEventHandlerTest )
{
    StdAsync exec;
    AnyEventDispatcher disp( 1, 10 );
    
    Int eventId1 = 0;    

    AnyEventHandler hand1( exec,
    [&] ( const AnyEvent& event )
    {
        eventId1 = event.Id();
    });

    disp.LinkTarget( hand1 );
    disp.DispatchEvent( 3 );

    // Wait the tasks are executed.
    Task< void > end( "End", [] {} );
    exec.Submit( end );
    end.Wait();

    CHECK( 3 == eventId1 );


    //
    // NOTES:
    //   The below snippet won't compile,
    //   because a lambda can not access itself in its own code.
    //
    // AnyEventHandler hand2( exec,
    // [&] ( const AnyEvent& event )
    // { 
    //     disp.UnlinkTarget( hand2 );  // <- hand2 is unknown here.
    // });
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE AnyEventHandlerSuite

} // namespace Caramel
