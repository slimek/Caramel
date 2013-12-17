// Caramel C++ Library Test - Value - Any Test

#include "CaramelTestPch.h"

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


TEST( AnyNumberTest )
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


///////////////////////////////////////////////////////////////////////////////

} // SUITE AnySuite

} // namespace Caramel
