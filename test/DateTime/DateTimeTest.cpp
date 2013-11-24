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

    CHECK( 5025 == span2.TotalSeconds() );


    /// Operations between DateTime and TimeSpan ///

    const auto time2 = DateTime::FromString( "2013-04-05 00:00:00" );
    
    CHECK( time1 - time2 == TimeSpan::FromString( "18:09:30" ));

    const auto time3 = time2 + TimeSpan::FromString( "02:35:18" );

    CHECK( "2013-04-05 02:35:18" == time3.ToString() );

}


TEST( TimeSpanTest )
{
    /// Accessors ///
    {
        const TimeSpan time0;

        CHECK( 0 == time0.Days() );
        CHECK( 0 == time0.Hours() );
        CHECK( 0 == time0.Minutes() );
        CHECK( 0 == time0.Seconds() );

        CHECK( 0 == time0.TotalDays() );
        CHECK( 0 == time0.TotalHours() );
        CHECK( 0 == time0.TotalMinutes() );
        CHECK( 0 == time0.TotalSeconds() );

        const auto time1 = TimeSpan::FromString( "12:30:00" );

        CHECK( 0  == time1.Days() );
        CHECK( 12 == time1.Hours() );
        CHECK( 30 == time1.Minutes() );
        CHECK( 0  == time1.Seconds() );

        CHECK( 12.5 / 24.0 == time1.TotalDays() );
        CHECK( 12.5        == time1.TotalHours() );
        CHECK( 750         == time1.TotalMinutes() );
        CHECK( 45000       == time1.TotalSeconds() );

        const auto time2 = TimeSpan::FromString( "1:40:05" );

        CHECK( 0  == time2.Days() );
        CHECK( 1  == time2.Hours() );
        CHECK( 40 == time2.Minutes() );
        CHECK( 5  == time2.Seconds() );

        CHECK( 6005.0 / 86400.0 == time2.TotalDays() );
        CHECK( 6005.0 / 3600.0  == time2.TotalHours() );
        CHECK( 6005.0 / 60.0    == time2.TotalMinutes() );
        CHECK( 6005             == time2.TotalSeconds() );

        const auto time3 = TimeSpan::FromString( "125:45:08" );

        CHECK( 5  == time3.Days() );
        CHECK( 5  == time3.Hours() );
        CHECK( 45 == time3.Minutes() );
        CHECK( 8  == time3.Seconds() );

        CHECK( 452708.0 / 86400.0 == time3.TotalDays() );
        CHECK( 452708.0 / 3600.0  == time3.TotalHours() );
        CHECK( 452708.0 / 60.0    == time3.TotalMinutes() );
        CHECK( 452708             == time3.TotalSeconds() );
    }
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE DateTimeSuite

} // namespace Caramel

