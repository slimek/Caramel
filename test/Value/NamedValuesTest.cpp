// Caramel C++ Library Test - Value - Named Values Test

#include "CaramelTestPch.h"

#include <Caramel/Value/NamedValues.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( NamedValuesSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Named Values Test
//

TEST( NamedValuesTest )
{
    NamedValues nv;

    nv[ "miko" ] = "Reimu";

    std::string s = nv[ "miko" ].AsString();

    //CHECK( "Reimu" == nv[ "miko" ].AsString() );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE NamedValuesSuite

} // namespace Caramel
