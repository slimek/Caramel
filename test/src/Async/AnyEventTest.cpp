// Caramel C++ Library Test - Async - Any Event Test

#include "CaramelTestPch.h"

#include <Caramel/Async/AnyEvent.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( AnyEventSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Test
//

TEST( AnyEventTest )
{
    auto evt1 = AnyEvent( 1 );           // empty event;
    auto evt2 = AnyEvent( 2, "Alice" );
    auto evt3 = AnyEvent( 3, 42 );

    CHECK( 1 == evt1.Id() );
    
    CHECK( 2 == evt2.Id() );
    CHECK( "Alice" == evt2.Value< std::string >() );
    
    CHECK( 3 == evt3.Id() );
    CHECK( 42 == evt3.Value< Int >() );
    CHECK( 42 == evt3.Value< Uint >() );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE AnyEventSuite

} // namespace Caramel