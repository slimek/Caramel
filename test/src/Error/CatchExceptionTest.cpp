// Caramel C++ Library Test - Error - Catch Exception Test

#include "CaramelTestPch.h"

#include <Caramel/Error/CatchException.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( CatchExceptionSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Catch Exception Test
//

TEST( CatchExceptionTest )
{
    /// No Exception ///
    {
        auto x = CatchException( [] { ; } );

        CHECK( false == x );

        ExceptionPtr px = x.GetException();
    
        CHECK( false == px );
    }


    /// Exception ///
    {
        auto x = CatchException( [] { CARAMEL_THROW( "Alice in Shanghai" ); } );

        CHECK ( true == x );

        ExceptionPtr px = x.GetException();

        try
        {
            px.Rethrow();
        }
        catch ( const Exception& e )
        {
            CHECK( "Alice in Shanghai" == e.What() );
        }
        catch ( ... )
        {
            CHECK( ! "Not reached" );
        }
    }

    /// Any Failure ///
    {
        auto x = CatchException( [] { throw AnyFailure( 42, "The Answer" ); } );

        CHECK( true == x );

        ExceptionPtr px = x.GetException();

        try
        {
            px.Rethrow();
        }
        catch ( const AnyFailure& fx )
        {
            CHECK( 42 == fx.Id() );
            CHECK( "The Answer" == fx.Value< std::string >() );
        }
        catch ( ... )
        {
            CHECK( ! "Not reached" );
        }
    }

    /// Access Violation ///
    {
        auto x = CatchException(
        []
        {
            Int* pi = nullptr;
            ++ *pi;
        });

        CHECK( true == x );

        ExceptionPtr px = x.GetException();

        try
        {
            px.Rethrow();
        }
        catch ( const std::exception& e )
        {
            CHECK( 0 == strcmp( "Access Violation", e.what() ));
        }
        catch ( ... )
        {
            CHECK( ! "Not reached" );
        }
    }
}


} // SUITE CatchExceptionSuite

} // namespace Caramel
