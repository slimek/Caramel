// Caramel C++ Library Test - Error - Exception Ptr Suite

#include "CaramelTestPch.h"

#include <Caramel/Error/AnyFailure.h>
#include <Caramel/Error/ExceptionPtr.h>
#include <cstring>


namespace Caramel
{

SUITE( ExceptionPtr )
{

TEST( ExceptionPtrNull )
{
    ExceptionPtr px0;

    CHECK( ! px0 );
    CHECK( nullptr == px0 );

    ExceptionPtr px1( nullptr );

    CHECK( ! px1 );
    CHECK( nullptr == px1 );

    ExceptionPtr px2;
    px2 = nullptr;

    CHECK( ! px2 );
    CHECK( nullptr == px2 );

    // Null ExceptionPtr should be equal.
    CHECK( px1 == px2 );
}


TEST( ExceptionPtr )
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
        CHECK( 42 == fx.Code() );
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


TEST( AnyFailurePtrNull )
{
    AnyFailurePtr af0;

    CHECK( ! af0 );
    CHECK( nullptr == af0 );

    AnyFailurePtr af1( nullptr );

    CHECK( ! af1 );
    CHECK( nullptr == af1 );

    AnyFailurePtr af2;
    af2 = nullptr;

    CHECK( ! af2 );
    CHECK( nullptr == af2 );
}


TEST( AnyFailurePtr )
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

    AnyFailurePtr pf1 = AnyFailurePtr::CastFrom( px1 );

    CHECK( ! pf1 );
    CHECK( nullptr == pf1.operator->() );


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

    AnyFailurePtr pf2 = AnyFailurePtr::CastFrom( px2 );

    CHECK( pf2 );
    CHECK( pf2 == px2 );
    CHECK( 42 == pf2->Code() );
    CHECK( "The Big Answer" == pf2->What() );


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

    AnyFailurePtr pf3 = AnyFailurePtr::CastFrom( px3 );

    CHECK( ! pf3 );
    CHECK( nullptr == pf3.operator->() );
}


} // SUITE ExceptionPtr

} // namespace Caramel
