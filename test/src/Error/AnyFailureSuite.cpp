// Caramel C++ Library Test - Error - Any Failure Suite

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEvent.h>
#include <Caramel/Async/AnyEventQueue.h>
#include <Caramel/Error/AnyFailure.h>
#include <Caramel/Error/ExceptionPtr.h>
#include <UnitTest++/UnitTest++.h>
#include <cstring>


namespace Caramel
{

SUITE( AnyFailureSuite )
{

TEST( AnyFailureTest )
{
    try
    {
        throw AnyFailure( 42 );
    }
    catch ( const std::exception& x )
    {
        CHECK( 0 == std::strcmp( "AnyFailure[code:42]", x.what() ));
    }


    try
    {
        throw AnyFailure( 42, "The Answer" );
    }
    catch ( const AnyFailure& fx )
    {
        CHECK( 42 == fx.Code() );
        CHECK( "The Answer" == fx.Value< std::string >() );
        CHECK( false == fx.HasCustomWhat() );
    }
    catch ( const std::exception& )
    {
        CHECK( ! "Not reached" );
    }


    ExceptionPtr px;

    try
    {
        throw AnyFailure( 216 ).What( "Triple Six" );
    }
    catch ( ... )
    {
        px = CurrentException();
    }

    try
    {
        px.Rethrow();
    }
    catch ( const AnyFailure& fx )
    {
        CHECK( 216 == fx.Code() );
        CHECK( "Triple Six" == fx.What() );
        CHECK( true == fx.HasCustomWhat() );
    }
}


} // SUITE AnyFailureSuite

} // namespace Caramel
