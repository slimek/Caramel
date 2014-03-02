// Caramel C++ Library Test - Error - Exception Ptr Test

#include "CaramelTestPch.h"

#include <Caramel/Error/AnyFailure.h>
#include <Caramel/Error/ExceptionPtr.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( ExceptionPtrSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Exception Ptr Test
//

TEST( ExceptionPtrTest )
{
    /// std::exception ///

    ExceptionPtr px1;

    try
    {
        throw std::logic_error( "Alice in Shanghai" );
    }
    catch ( ... )
    {
        px1 = CurrentException();
    }

    try
    {
        px1.Rethrow();
    }
    catch ( const std::exception& x )
    {
        CHECK( 0 == std::strcmp( "Alice in Shanghai", x.what() ));
    }


    /// AnyFailure ///

    ExceptionPtr px2;

    try
    {
        throw AnyFailure( 42 ).What( "The Big Answer" );
    }
    catch ( ... )
    {
        px2 = CurrentException();
    }

    try
    {
        px2.Rethrow();
    }
    catch ( const AnyFailure& fx )
    {
        CHECK( 42 == fx.Id() );
        CHECK( "The Big Answer" == fx.What() );
    }
    catch ( ... )
    {
        CHECK( ! "Not reached" );
    }


    /// Exception ///

    ExceptionPtr px3;

    try
    {
        CARAMEL_THROW( "Spell Break!" );
    }
    catch ( ... )
    {
        px3 = CurrentException();
    }

    try
    {
        px3.Rethrow();
    }
    catch ( const Exception& ex )
    {
        CHECK( "Spell Break!" == ex.What() );
    }
    catch ( ... )
    {
        CHECK( ! "Not reached" );
    }
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE ExceptionPtrSuite

} // namespace Caramel
