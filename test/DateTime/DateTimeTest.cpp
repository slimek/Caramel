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
    CHECK( "2013-04-05T18:09:30" == time1.ToIsoString() );

    const auto span1 = TimeSpan::FromString( "22:08:19" );

    CHECK( "22:08:19" == span1.ToString() );

    const auto span2 = TimeSpan::FromString( "01:23:45" );

    CHECK( Seconds( 5025 ) == span2.TotalSeconds() );


    /// Operations between DateTime and TimeSpan ///

    const auto time2 = DateTime::FromString( "2013-04-05 00:00:00" );
    
    CHECK( time1 - time2 == TimeSpan::FromString( "18:09:30" ));

    const auto time3 = time2 + TimeSpan::FromString( "02:35:18" );

    CHECK( "2013-04-05 02:35:18" == time3.ToString() );

}


TEST( TimeSpanTest )
{
    const TimeSpan time0;

    CHECK( 0 == time0.TotalHours() );
    CHECK( Seconds::Zero() == time0.TotalSeconds() );

    const auto time1 = TimeSpan::FromString( "12:30:00" );

    CHECK( 12.5 == time1.TotalHours() );
    CHECK( Seconds( 45000 ) == time1.TotalSeconds() );

    const auto time2 = TimeSpan::FromString( "1:40:05" );

    CHECK( 6005.0 / 3600.0 == time2.TotalHours() );
    CHECK( Seconds( 6005 ) == time2.TotalSeconds() );

}


///////////////////////////////////////////////////////////////////////////////

} // SUITE DateTimeSuite

} // namespace Caramel

