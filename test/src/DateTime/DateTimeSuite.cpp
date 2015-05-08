// Caramel C++ Library Test - DateTime - Date Time Suite

#include "CaramelTestPch.h"

#include <Caramel/DateTime/DateTime.h>


namespace Caramel
{

SUITE( DateTime )
{

TEST( DateTimeBasic )
{
    const DateTime undef;
    const auto now = DateTime::Now();
    const auto min = DateTime::MinValue();
    const auto max = DateTime::MaxValue();

    CHECK( false == undef.IsValid() );
    CHECK( true  == now.IsValid() );
    CHECK( min < now && now < max );

    //
    // Limit values: these are Boost.DateTime spec
    //

    CHECK( "1400-01-01 00:00:00"        == min.ToString() );
    CHECK( "9999-12-31 23:59:59.999999" == max.ToString() );

    CHECK( 1400 == min.Year() );
    CHECK( 1 == min.Month() );
    CHECK( 1 == min.Day() );
    CHECK( 0 == min.Hour() );
    CHECK( 0 == min.Minute() );
    CHECK( 0 == min.Second() );
    CHECK( 0 == min.Millisecond() );

    CHECK( 9999 == max.Year() );
    CHECK( 12 == max.Month() );
    CHECK( 31 == max.Day() );
    CHECK( 23 == max.Hour() );
    CHECK( 59 == max.Minute() );
    CHECK( 59 == max.Second() );
    CHECK( 999 == max.Millisecond() );
}


TEST( DateTimeString )
{
    const auto time1 = DateTime::FromString( "2013-04-05 18:09:30" );

    CHECK( "2013-04-05 18:09:30" == time1.ToString() );
    CHECK( "2013-04-05T18:09:30" == time1.ToIsoString() );
    CHECK( "20130405T180930" == time1.ToIsoBasicString() );

    const auto span1 = TimeSpan::FromString( "22:08:19" );

    CHECK( "22:08:19" == span1.ToString() );

    const auto span2 = TimeSpan::FromString( "01:23:45" );

    CHECK( 5025 == span2.TotalSeconds() );


    /// Try Parse ///

    DateTime dt;

    CHECK( false == dt.TryParse( "" ));  // empty string
    CHECK( false == dt.TryParse( "12" ));
    CHECK( false == dt.TryParse( "20140315" ));

    CHECK( true  == dt.TryParse( "2014-03-15 08:23:14" ));
    CHECK( dt == Date( 2014, 3, 15 ) + TimeOfDay( 8, 23, 14 ));

    CHECK( true  == dt.TryParse( "1984/05/06 17:28:39" ));
    CHECK( dt == Date( 1984, 5, 6 ) + TimeOfDay( 17, 28, 39 ));


    /// From ISO String ///

    const auto dt1 = DateTime::FromString( "2013-04-05T18:09:30" );
    CHECK( dt1 == Date( 2013, 4, 5 ) + TimeOfDay( 18, 9, 30 ));

    DateTime dt2;

    CHECK( true == dt2.TryParse( "2014-03-15T08:23:14" ));
    CHECK( dt2 == Date( 2014, 3, 15 ) + TimeOfDay( 8, 23, 14 ));

    // With UTC 'Z' designator
    CHECK( true == dt2.TryParse( "1984-05-06T17:28:39Z" ));
    CHECK( dt2 == Date( 1984, 5, 6 ) + TimeOfDay( 17, 28, 39 ));

    // ISO 8601 with Time Zone is not supported.
    CHECK( false == dt2.TryParse( "2013-04-16T07:28:39+08:00" ));

    // You may omit seconds.
    const auto dt3 = DateTime::FromString( "2013-04-05T18:09" );
    CHECK( dt3 == Date( 2013, 4, 5 ) + TimeOfDay( 18, 9, 0 ));

    // With milliseconds
    // - The fraction less than milliseconds are dropped.
    const auto dt4 = DateTime::FromString( "2013-04-05T18:09:27.345" );
    CHECK( dt4.Millisecond() == 345 );
    const auto dt5 = DateTime::FromString( "2013-04-05T18:09:27.234567" );
    CHECK( dt5.Millisecond() == 234 );
}


TEST( DateTimeFormat )
{
    const auto dt = DateTime::FromString( "2013-04-05 6:17:28" );

    CHECK( "2013/04/05" == dt.Format( "%Y/%m/%d" ));
    CHECK( "06:17:28"   == dt.Format( "%H:%M:%S" ));
    
    CHECK( "April 05 '13 is Friday" == dt.Format( "%B %d '%y is %A" ));
}


TEST( DateTimeComparisons )
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


TEST( DateTimeArithmetic )
{
    const auto dt1 = DateTime::FromString( "2013-04-05 18:09:30" );
    const auto dt2 = DateTime::FromString( "2013-04-05 00:00:00" );
    
    CHECK( dt1 - dt2 == TimeSpan::FromString( "18:09:30" ));

    const auto dt3 = dt2 + TimeSpan::FromString( "02:35:18" );

    CHECK( "2013-04-05 02:35:18" == dt3.ToString() );

    const auto dt4 = dt2 - TimeSpan::FromString( "15:47:36" );

    CHECK( "2013-04-04 08:12:24" == dt4.ToString() );

    const auto dt5 = dt4 - Milliseconds( 1400 );

    CHECK( "2013-04-04 08:12:22.600000" == dt5.ToString() );

    const auto dt6 = dt5 + Seconds( 2.75 );

    CHECK( "2013-04-04 08:12:25.350000" == dt6.ToString() );
}


TEST( DateAndTimeOfDay )
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
        const auto dt1 = DateTime::FromString( "1987/06/05 4:32:10" );

        CHECK( Date( 1987, 6, 5 ) == dt1.Date() );
        CHECK( TimeOfDay( 4, 32, 10 ) == dt1.TimeOfDay() );
    }
}


TEST( DateTimeOpDays )
{
    const auto dt = DateTime::FromString( "2013/04/05 6:17:28" );

    CHECK( DateTime::FromString( "2013/05/04 6:17:28" ) == dt + Days( 29 ));
    CHECK( DateTime::FromString( "2013/03/31 6:17:28" ) == dt - Days( 5 ));
}


TEST( DateTimeUtc )
{
    const auto now = DateTime::Now();
    const auto utcNow = DateTime::UtcNow();

    const auto localNow = DateTime::UtcToLocal( utcNow );

    CHECK_CLOSE( 0, ( localNow - now ).TotalSeconds(), 1 );
}


} // SUITE DateTime

} // namespace Caramel
