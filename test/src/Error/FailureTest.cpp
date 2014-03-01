// Caramel C++ Library Test - Error - Failure Test

#include "CaramelTestPch.h"

#include <Caramel/Error/Failure.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( FailureSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Failure Test
//

TEST( FailureTest )
{
    try
    {
        throw Failure( 42 );
    }
    catch ( const std::exception& x )
    {
        CHECK( 0 == std::strcmp( "code: 42", x.what() ));
    }


    try
    {
        throw Failure( 42, "The Answer" );
    }
    catch ( const Failure& fx )
    {
        CHECK( 42 == fx.Code() );
        CHECK( "The Answer" == fx.What() );
    }
    catch ( const std::exception& )
    {
        CHECK( ! "Not reached" );
    }


    std::exception_ptr px;

    try
    {
        throw Failure( 216, "Triple Six" );
    }
    catch ( ... )
    {
        px = std::current_exception();
    }

    try
    {
        std::rethrow_exception( px );
    }
    catch ( const Failure& fx )
    {
        CHECK( 216 == fx.Code() );
        CHECK( "Triple Six" == fx.What() );
    }
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE FailureSuite

} // namespace Caramel
