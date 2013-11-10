// Caramel C++ Library Test - DateTime - Date Time Test

#include "CaramelTestPch.h"

#include <Caramel/DateTime/DateTime.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( DateTimeSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Date Time Test
//

TEST( DateTimeTest )
{
    const auto now = DateTime::Now();

    const auto time1 = DateTime::FromString( "2013-04-05 18:09:30" );

    CHECK( "2013-04-05 18:09:30" == time1.ToString() );
    CHECK( "20130405T180930" == time1.ToIsoString() );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE DateTimeSuite

} // namespace Caramel

