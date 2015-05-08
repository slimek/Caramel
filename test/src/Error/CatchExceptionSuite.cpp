// Caramel C++ Library Test - Error - Catch Exception Suite

#include "CaramelTestPch.h"

#include <Caramel/Error/CatchException.h>


namespace Caramel
{

SUITE( CatchException )
{

TEST( CatchException )
{
    /// No Exception ///
    {
        auto xc = CatchException( [] { ; } );

        CHECK( ! xc );
        CHECK( ! xc.AnyFailure() );
        CHECK( ! xc.Exception() );

        ExceptionPtr px = xc.Exception();
        CHECK( ! px );
    }


    /// Caramel::Exception ///
    {
        auto xc = CatchException( [] { CARAMEL_THROW( "Alice in Shanghai" ); } );

        CHECK( xc );
        CHECK( ! xc.AnyFailure() );
        CHECK( xc.Exception() );

        ExceptionPtr px = xc.Exception();

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
        auto xc = CatchException( [] { throw AnyFailure( 42, "The Answer" ); } );

        CHECK( xc );
        CHECK( xc.AnyFailure() );
        CHECK( xc.Exception() );

        ExceptionPtr px = xc.Exception();

        try
        {
            px.Rethrow();
        }
        catch ( const AnyFailure& fx )
        {
            CHECK( 42 == fx.Code() );
            CHECK( "The Answer" == fx.Value< std::string >() );
        }
        catch ( ... )
        {
            CHECK( ! "Not reached" );
        }

        AnyFailurePtr paf = xc.AnyFailure();

        CHECK( 42 == paf->Code() );
        CHECK( "The Answer" == paf->Value< std::string >() );


        // The two exception pointers should be the same.
        CHECK( px == paf );
    }

    
    /// Access Violation - Only for Win32 ///
    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    {
        auto xc = CatchException(
        []
        {
            Int* pi = nullptr;
            ++ *pi;
        });

        CHECK( xc );

        ExceptionPtr px = xc.Exception();

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
    #endif // CARAMEL_SYSETM_IS_WINDOWS
}


TEST( CatchExceptionWithResult )
{
    /// Exception ///
    {
        auto xc = CatchException( [] { CARAMEL_THROW( "Alice in Shanghai" ); return false; } );

        CHECK( xc );
        CHECK(( true == std::is_same< Bool, decltype( xc.Result() ) >::value ));

        try
        {
            xc.Exception().Rethrow();
        }
        catch ( const Exception& x )
        {
            CHECK( "Alice in Shanghai" == x.What() );
        }
        catch ( ... )
        {
            CHECK( ! "Not reached" );
        }
    }

    /// Any Exception ///
    {
        auto xc = CatchException( [] { throw AnyFailure( 42, "The Answer" ); return 126; } );

        CHECK( xc );
        CHECK(( true == std::is_same< Int, decltype( xc.Result() ) >::value ));

        try
        {
            xc.Exception().Rethrow();
        }
        catch ( const AnyFailure& fx )
        {
            CHECK( 42 == fx.Code() );
            CHECK( "The Answer" == fx.Value< std::string >() );
        }
        catch ( ... )
        {
            CHECK( ! "Not reached" );
        }
    }

    /// Access Violation - Only for Win32 ///
    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    {
        auto xc = CatchException(
        []
        {
            Int* pi = nullptr;
            ++ *pi;
            return std::string( "Marisa" );
        });

        CHECK( xc );
        CHECK(( true == std::is_same< std::string, decltype( xc.Result() ) >::value ));

        try
        {
            xc.Exception().Rethrow();
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
    #endif // CARAMEL_SYSTEM_IS_WINDOWS
}


} // SUITE CatchException

} // namespace Caramel
