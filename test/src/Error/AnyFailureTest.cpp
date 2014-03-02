// Caramel C++ Library Test - Error - Any Failure Test

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEvent.h>
#include <Caramel/Async/AnyEventQueue.h>
#include <Caramel/Error/AnyFailure.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( AnyFailureSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Failure Test
//

TEST( AnyFailureTest )
{
    try
    {
        throw AnyFailure( 42 );
    }
    catch ( const std::exception& x )
    {
        CHECK( 0 == std::strcmp( "AnyFailure[id:42]", x.what() ));
    }


    try
    {
        throw AnyFailure( 42, "The Answer" );
    }
    catch ( const AnyFailure& fx )
    {
        CHECK( 42 == fx.Id() );
        CHECK( "The Answer" == fx.Value< std::string >() );
        CHECK( false == fx.HasCustomWhat() );
    }
    catch ( const std::exception& )
    {
        CHECK( ! "Not reached" );
    }


    std::exception_ptr px;

    try
    {
        throw AnyFailure( 216 ).What( "Triple Six" );
    }
    catch ( ... )
    {
        px = std::current_exception();
    }

    try
    {
        std::rethrow_exception( px );
    }
    catch ( const AnyFailure& fx )
    {
        CHECK( 216 == fx.Id() );
        CHECK( "Triple Six" == fx.What() );
        CHECK( true == fx.HasCustomWhat() );
    }
}


TEST( AnyFailureToEventTest )
{
    AnyEventQueue queue;

    try
    {
        throw AnyFailure( 42, "The Answer" );
    }
    catch ( const AnyFailure& fx )
    {
        AnyEvent evt = fx.ToAnyEvent();
        queue.Push( evt );
    }
    catch ( ... )
    {
        CHECK( ! "Not reached" );
    }

    AnyEvent evt;
    CHECK( true == queue.TryPop( evt ));

    CHECK( 42 == evt.Id() );
    CHECK( "The Answer" == evt.Value< std::string >() );

}


///////////////////////////////////////////////////////////////////////////////

} // SUITE AnyFailureSuite

} // namespace Caramel
