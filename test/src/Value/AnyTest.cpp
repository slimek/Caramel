// Caramel C++ Library Test - Value - Any Test

#include "CaramelTestPch.h"

#include <Caramel/Value/Any.h>
#include <UnitTest++/UnitTest++.h>
#include <boost/any.hpp>


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
    
    CHECK( 42 == ai.To< Int >() );
    CHECK( 42 == ai.To< Uint >() );

    Any au( 216u );

    CHECK( 216 == au.To< Int >() );
    CHECK( 216 == au.To< Uint >() );


    /// Out of Range would throw exceptions ///

    Any aux( 0xFFFFFFFF );

    CHECK( 0xFFFFFFFF == aux.To< Uint >() );
    CHECK_THROW( aux.To< Int >(), Caramel::Exception );

    Any aii( -1 );

    CHECK( -1 == aii.To< Int >() );
    CHECK_THROW( aii.To< Uint >(), Caramel::Exception );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE AnySuite

} // namespace Caramel
