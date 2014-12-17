// Caramel C++ Library Test - Async - Value Change Suite

#include "CaramelTestPch.h"

#include <Caramel/Async/ValueChange.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( ValueChangeSuite )
{

TEST( ValueChangeIntTest )
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


TEST( ValueChangeBoolTest )
{
    ValueChange< Bool > b1;  // default initial to false.

    CHECK( false == b1.Enters< false >() );
    CHECK( false == b1.Enters< true >() );
    CHECK( false == b1.Exits< false >() );
    CHECK( false == b1.Exits< true >() );

    b1.Update( true );

    CHECK( false == b1.Enters< false >() );
    CHECK( true  == b1.Enters< true >() );
    CHECK( true  == b1.Exits< false >() );
    CHECK( false == b1.Exits< true >() );

    b1.Update( true );

    CHECK( false == b1.Enters< false >() );
    CHECK( false == b1.Enters< true >() );
    CHECK( false == b1.Exits< false >() );
    CHECK( false == b1.Exits< true >() );

    b1.Update( false );

    CHECK( true  == b1.Enters< false >() );
    CHECK( false == b1.Enters< true >() );
    CHECK( false == b1.Exits< false >() );
    CHECK( true  == b1.Exits< true >() );

    b1.Update( false );

    CHECK( false == b1.Enters< false >() );
    CHECK( false == b1.Enters< true >() );
    CHECK( false == b1.Exits< false >() );
    CHECK( false == b1.Exits< true >() );


    ValueChange< Bool > b2( true );  // with initial value

    CHECK( false == b2.Enters< false >() );
    CHECK( false == b2.Enters< true >() );
    CHECK( false == b2.Exits< false >() );
    CHECK( false == b2.Exits< true >() );

    b2.Update( false );

    CHECK( true  == b2.Enters< false >() );
    CHECK( false == b2.Enters< true >() );
    CHECK( false == b2.Exits< false >() );
    CHECK( true  == b2.Exits< true >() );
}


} // SUITE ValueChangeSuite

} // namespace Caramel
