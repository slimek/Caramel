// Caramel C++ Library Test - Error - Std Exception Ptr Test

#include "CaramelTestPch.h"

#include <Caramel/Error/Failure.h>
#include <Caramel/Error/StdExceptionPtr.h>
#include <UnitTest++/UnitTest++.h>
#include <iostream>


namespace Caramel
{

SUITE( StdExceptionPtrSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Std Exception Ptr Test
//

TEST( StdExceptionPtrTest )
{
    /// std::exception ///

    StdExceptionPtr px1;

    try
    {
        throw std::logic_error( "Alice in Shanghai" );
    }
    catch ( ... )
    {
        px1 = CurrentStdException();
    }

    try
    {
        px1.Rethrow();
    }
    catch ( const std::exception& x )
    {
        CHECK( 0 == std::strcmp( "Alice in Shanghai", x.what() ));
    }


    /// Failure ///

    StdExceptionPtr px2;

    try
    {
        throw Failure( 42, "The Big Answer" );
    }
    catch ( ... )
    {
        px2 = CurrentStdException();
    }

    try
    {
        px2.Rethrow();
    }
    catch ( const Failure& fx )
    {
        CHECK( 42 == fx.Code() );
        CHECK( "The Big Answer" == fx.What() );
    }
    catch ( ... )
    {
        CHECK( ! "Not reached" );
    }


    /// Exception ///

    StdExceptionPtr px3;

    try
    {
        CARAMEL_THROW( "Spell Break!" );
    }
    catch ( ... )
    {
        px3 = CurrentStdException();
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

} // SUITE StdExceptionPtrSuite

} // namespace Caramel
