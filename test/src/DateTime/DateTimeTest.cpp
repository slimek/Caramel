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

TEST( DateTimeBasicTest )
{
    const DateTime undef;
    const auto now = DateTime::Now();
    const auto min = DateTime::MinValue();
    const auto max = DateTime::MaxValue();

    CHECK( false == undef.IsValid() );
    CHECK( true  == now.IsValid() );
    CHECK( min < now && now < max );

    // Limit values: these are Boost.DateTime spec
    CHECK( "1400-01-01 00:00:00"        == min.ToString() );
    CHECK( "9999-12-31 23:59:59.999999" == max.ToString() );
}


TEST( DateTimeStringTest )
{
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

    const auto time4 = time2 - TimeSpan::FromString( "15:47:36" );

    CHECK( "2013-04-04 08:12:24" == time4.ToString() );


    /// Try Parse ///

    DateTime dt;

    CHECK( false == dt.TryParse( "" ));  // empty string
    CHECK( false == dt.TryParse( "12" ));
    CHECK( false == dt.TryParse( "20140315" ));

    CHECK( true  == dt.TryParse( "2014-03-15 08:23:14" ));
    CHECK( dt == Date( 2014, 3, 15 ) + TimeOfDay( 8, 23, 14 ));

    
    /// From ISO String ///

    const auto dt1 = DateTime::FromString( "2013-04-05T18:09:30" );
    CHECK( dt1 == Date( 2013, 4, 5 ) + TimeOfDay( 18, 9, 30 ));

    DateTime dt2;

    CHECK( true == dt2.TryParse( "2014-03-15T08:23:14" ));
    CHECK( dt2 == Date( 2014, 3, 15 ) + TimeOfDay( 8, 23, 14 ));
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


TEST( TimeOfDayTest )
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


TEST( DateTimeOpDaysTest )
{
    const auto dt = DateTime::FromString( "2013/04/05 6:17:28" );

    CHECK( DateTime::FromString( "2013/05/04 6:17:28" ) == dt + Days( 29 ));
    CHECK( DateTime::FromString( "2013/03/31 6:17:28" ) == dt - Days( 5 ));
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE DateTimeSuite

} // namespace Caramel

