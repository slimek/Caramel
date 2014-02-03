// Caramel C++ Library Test - Async - Value Change Test

#include "CaramelTestPch.h"

#include <Caramel/Async/ValueChange.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( ValueChangeSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Value Change Test
//

TEST( IntValueChangeTest )
{
    ValueChange< Int > ichange( 0 );

    CHECK( false == ichange.Enters< 1 >() );
    CHECK( false == ichange.Exits< 1 >() );

    ichange.Update( 1 );

    CHECK( true  == ichange.Enters< 1 >() );
    CHECK( false == ichange.Exits< 1 >() );

    ichange.Update( 1 );

    CHECK( false == ichange.Enters< 1 >() );
    CHECK( false == ichange.Exits< 1 >() );

    ichange.Update( 2 );

    CHECK( false == ichange.Enters< 1 >() );
    CHECK( true  == ichange.Exits< 1 >() );

    ichange.Update( 3 );

    CHECK( false == ichange.Enters< 1 >() );
    CHECK( false == ichange.Exits< 1 >() );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE ValueChangeSuite

} // namespace Caramel
