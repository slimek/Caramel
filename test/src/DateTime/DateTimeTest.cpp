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


    /// Valid Test ///

    const DateTime dtnil;  // not initialized / not a date-time

    CHECK( true  == now.IsValid() );
    CHECK( true  == time1.IsValid() );
    CHECK( false == dtnil.IsValid() );
}


TEST( DateTimeFormatTest )
{
    const auto dt = DateTime::FromString( "2013-04-05 6:17:28" );

    CHECK( "2013/04/05" == dt.Format( "%Y/%m/%d" ));
    CHECK( "06:17:28"   == dt.Format( "%H:%M:%S" ));
    
    CHECK( "April 05 '13 is Friday" == dt.Format( "%B %d '%y is %A" ));
}


TEST( DateTimeComparisonsTest )
{
    const auto dt1 = DateTime::FromString( "1987-06-23 4:56" );
    const auto dt2 = DateTime::FromString( "2013-04-05 6:17" );

    CHECK( dt1 != dt2 );
    CHECK( dt1 <  dt2 );
    CHECK( dt1 <= dt2 );
    CHECK( false == ( dt1 == dt2 ));
    CHECK( false == ( dt1 >  dt2 ));
    CHECK( false == ( dt1 >= dt2 ));

    const auto dt3 = dt1;

    CHECK( dt1 == dt3 );
    CHECK( dt1 <= dt3 );
    CHECK( dt1 >= dt3 );
    CHECK( false == ( dt1 != dt3 ));
    CHECK( false == ( dt1 <  dt3 ));
    CHECK( false == ( dt1 >  dt3 ));
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

        const TimeSpan time4( 42, 15, 5 );

        CHECK( 1  == time4.Days() );
        CHECK( 18 == time4.Hours() );
        CHECK( 15 == time4.Minutes() );
        CHECK( 5  == time4.Seconds() );
    }

    /// Comparison ///
    {
        const TimeSpan time0;
        const TimeSpan time1 = Hours( 5 ) + Minutes( 20 );
        const TimeSpan time2 = Hours( 6 ) - Minutes( 30 ) + Seconds( 15 );
        const TimeSpan time3 = time1;

        CHECK( TimeSpan::FromString( "0:00" )    == time0 );
        CHECK( TimeSpan::FromString( "5:20" )    == time1 );
        CHECK( TimeSpan::FromString( "5:30:15" ) == time2 );

        CHECK( time2 >  time1 );
        CHECK( time2 >= time1 );
        CHECK( time1 <  time2 );
        CHECK( time1 <= time2 );
        CHECK( time1 != time2 );
        
        CHECK( false == ( time1 >  time2 ));
        CHECK( false == ( time2 <  time1 ));
        CHECK( false == ( time1 == time2 ));

        CHECK( time1 == time1 + time0 );
        CHECK( time1 == time3 );
        CHECK( time1 <= time3 );
        CHECK( time1 >= time3 );
    }

    /// Cooperation with Seconds ///
    {
        const TimeSpan time0;
        const TimeSpan time1 = Hours( 5 ) + Minutes( 20 );
        const TimeSpan time2 = Seconds( 19200 );

        CHECK( time1 == time2 );

        const Seconds secs0 = time0;
        const Seconds secs1 = time1;

        CHECK( Seconds::Zero()  == secs0 );
        CHECK( Seconds( 19200 ) == secs1 );

        CHECK( secs0 == time0 );
        CHECK( secs1 == time1 );

        const Seconds secs2( 12000 );

        CHECK( secs2 <  time1 );
        CHECK( secs2 <= time1 );
        CHECK( time1 >  secs2 );
        CHECK( time1 >= secs2 );
        CHECK( time1 != secs2 );
        CHECK( secs2 != time1 );
        CHECK( false == ( secs2 >  time1 ));
        CHECK( false == ( secs2 >= time1 ));
        CHECK( false == ( time1 <  secs2 ));
        CHECK( false == ( time1 <= secs2 ));
        CHECK( false == ( time1 == secs2 ));
        CHECK( false == ( secs2 == time1 ));
    }

    /// Arithmetic ///
    {
        const TimeSpan t1( 0, 0, 42 );
        const TimeSpan t2( 0, 0, 3 );

        CHECK( TimeSpan( 0, 0, 45 ) == t1 + t2 );
        CHECK( TimeSpan( 0, 0, 39 ) == t1 - t2 );

        TimeSpan t3 = t1;
        t3 += Hours( 1 );
        CHECK( TimeSpan( 1, 0, 42 ) == t3 );

        TimeSpan t4 = t1;
        t4 -= Minutes( 30 );
        CHECK( -TimeSpan( 0, 29, 18 ) == t4 );

        CHECK( Seconds( 42 ) == t1 );  // t1 should not be modified
    }
}


TEST( TimeOfDay )
{
    const TimeOfDay td0;

    CHECK( TimeOfDay( 0, 0, 0 ) == td0 );

    const auto now = TimeOfDay::Now();
    const auto zero = TimeOfDay::FromString( "0:00:00" );

    CHECK( "00:00:00" == zero.ToString() );
    CHECK( TimeOfDay( 0, 0, 0 ) == zero );
    CHECK( 0 == zero.Hour() );
    CHECK( 0 == zero.Minute() );
    CHECK( 0 == zero.Second() );

    const auto tod1 = TimeOfDay::FromString( "12:34:56" );

    CHECK( "12:34:56" == tod1.ToString() );
    CHECK( TimeOfDay( 12, 34, 56 ) == tod1 );
    CHECK( 12 == tod1.Hour() );
    CHECK( 34 == tod1.Minute() );
    CHECK( 56 == tod1.Second() );

    CHECK( "23:59:59" == TimeOfDay::FromString( "23:59:59" ).ToString() );

    // Time of Day can be longer than a day
    CHECK_THROW( TimeOfDay( 24, 0, 0 ), Exception );
    CHECK_THROW( TimeOfDay::FromString( "24:00:00" ), Exception );

    // Time of Day can not be negative.
    CHECK_THROW( TimeOfDay( -1, 30, 15 ), Exception );
    CHECK_THROW( TimeOfDay::FromString( "-01:30:15" ), Exception );


    /// Comparisons ///

    const auto tod2 = TimeOfDay( 13, 45, 00 );

    CHECK( tod2 >  tod1 );
    CHECK( tod2 >= tod1 );
    CHECK( tod1 <  tod2 );
    CHECK( tod1 <= tod2 );
    CHECK( tod1 != tod2 );
    CHECK( false == ( tod1 > tod2 ));
    CHECK( false == ( tod2 < tod1 ));
    CHECK( false == ( tod1 == tod2 ));


    /// Cooperate with DateTime ///

    const auto dt0 = DateTime::FromString( "1900/1/1 00:00" );
    const auto dt1 = DateTime::FromString( "2013/5/7 14:30:15" );

    CHECK( TimeOfDay() == dt0.TimeOfDay() );
    CHECK( TimeOfDay( 14, 30, 15 ) == dt1.TimeOfDay() );
}


TEST( DateAndTimeOfDayTest )
{
    // Combine Date and TimeOfDay to DateTime
    {
        const auto date = Date::FromString( "2013/04/05" );
        const auto time = TimeOfDay::FromString( "6:17" );

        const auto dateTime = date + time;

        CHECK( "2013-04-05 06:17:00" == dateTime.ToString() );
    }

    // Split Date and TimeOfDay from DateTime
    {
        const auto dateTime = DateTime::FromString( "1987/06/05 4:32:10" );

        CHECK( Date( 1987, 6, 5 ) == dateTime.Date() );
        CHECK( TimeOfDay( 4, 32, 10 ) == dateTime.TimeOfDay() );
    }
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE DateTimeSuite

} // namespace Caramel

