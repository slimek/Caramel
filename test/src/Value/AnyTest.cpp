// Caramel C++ Library Test - Value - Any Test

#include "CaramelTestPch.h"

#include <Caramel/Numeric/NumberTraits.h>
#include <Caramel/Value/Any.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( AnySuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Test
//

TEST( AnyEmptyTest )
{
    Any a0;
    CHECK( true == a0.IsEmpty() );

    Any ai( 1 );
    CHECK( false == ai.IsEmpty() );
}


TEST( AnyIntegerTest )
{
    Any ai( 42 );
    
    CHECK( 42 == ai.As< Int >() );
    CHECK( 42 == ai.As< Uint >() );

    Any au( 216u );

    CHECK( 216 == au.As< Int >() );
    CHECK( 216 == au.As< Uint >() );


    /// Out of Range would throw exceptions ///

    Any aux( 0xFFFFFFFF );

    CHECK( 0xFFFFFFFF == aux.As< Uint >() );
    CHECK_THROW( aux.As< Int >(), Caramel::Exception );

    Any aii( -1 );

    CHECK( -1 == aii.As< Int >() );
    CHECK_THROW( aii.As< Uint >(), Caramel::Exception );


    /// Convert to Floating ///

    CHECK( 42.0 == ai.As< Double >() );
    CHECK( -1.0 == aii.As< Double >() );
    CHECK( (Double)0xFFFFFFFF == aux.As< Double >() );
}


TEST( AnyStringTest )
{
    Any as( std::string( "Alice" ));
    Any asz1( "Cirno" );

    Char* marisa = "Marisa";
    Any asz2( marisa );

    CHECK( "Alice"  == as.As< std::string >() );
    CHECK( "Cirno"  == asz1.As< std::string >() );
    CHECK( "Marisa" == asz2.As< std::string >() );

    // String type Any can only cast to std::string.
    // CHECK( as.As< const Char* >() );
}


enum Color
{
    COLOR_BLACK = 0,
    COLOR_BLUE  = 42,
};

enum FillMode
{
    FILL_BLANK = 0,
    FILL_SOLID = 255,
};

TEST( AnyEnumTest )
{
    Any ae( COLOR_BLUE );

    CHECK( 42         == ae.As< Int >() );
    CHECK( COLOR_BLUE == ae.As< Color >() );

    CHECK_THROW( ae.As< FillMode >(), Caramel::Exception );
}


TEST( AnyIntegerToFloatingTest )
{
    Any az( 0 );
    Any ai32max( INT32_MAX );
    Any ai32min( INT32_MIN );

    CHECK( 0 == az.As< Float >() );
    CHECK( 0 == az.As< Double >() );

    CHECK( INT32_MAX == ai32max.As< Double >() );
    CHECK( INT32_MIN == ai32min.As< Double >() );

    CHECK_THROW( ai32max.As< Float >(), Caramel::Exception );
    CHECK_THROW( ai32min.As< Float >(), Caramel::Exception );

    
    /// Conversion Limits ///

    const Int32 i32femax = NumberTraits< Float >::MAX_EXACT_INT32;
    const Int32 i32femin = NumberTraits< Float >::MIN_EXACT_INT32;

    Any ai32femax( i32femax );
    Any ai32femin( i32femin );

    CHECK( i32femax == ai32femax.As< Float >() );
    CHECK( i32femin == ai32femin.As< Float >() );

    Any ai32feover ( i32femax + 1 );
    Any ai32feunder( i32femin - 1 );

    CHECK_THROW( ai32feover.As< Float >(),  Caramel::Exception );
    CHECK_THROW( ai32feunder.As< Float >(), Caramel::Exception );
}


TEST( AnyFloatingTest )
{
    Any az( 0.0 );
    Any as( 42.0 );
    Any ap( 3.1416 );

    Any afmin( FLT_MIN );
    Any afpmax( FLT_MAX );
    Any afnmax( -FLT_MAX );
    Any afeps( FLT_EPSILON );

    Any admax( DBL_MAX );

    CHECK( 0.0f == az.As< Float >() );
    CHECK( 0.0  == az.As< Double >() );

    CHECK( 42.0f == as.As< Float >() );
    CHECK( 42.0  == as.As< Double >() );

    CHECK( 3.1416f == ap.As< Float >() );
    CHECK( 3.1416  == ap.As< Double >() );

    CHECK(  FLT_MIN == afmin.As< Float >() );
    CHECK(  FLT_MAX == afpmax.As< Float >() );
    CHECK( -FLT_MAX == afnmax.As< Float >() );
    CHECK(  FLT_EPSILON == afeps.As< Float >() );

    CHECK( DBL_MAX == admax.As< Double >() );
    CHECK_THROW( admax.As< Float >(), Caramel::Exception );
}


TEST( AnyObjectTest )
{
    /// Pair Struct ///

    typedef std::pair< Int, std::string > IdName;

    IdName src;
    src.first  = 42;
    src.second = "Eirin";

    Any ain( src );

    IdName dest = ain.As< IdName >();

    CHECK( 42      == dest.first );
    CHECK( "Eirin" == dest.second );


    /// Smart Pointer ///

    std::shared_ptr< Float > real( new Float( 3.14f ));

    Any asp( real );

    CHECK( 3.14f == *( asp.As< std::shared_ptr< Float > >() ));
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE AnySuite

} // namespace Caramel
