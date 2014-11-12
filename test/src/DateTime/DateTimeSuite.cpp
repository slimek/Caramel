// Caramel C++ Library Test - DateTime - Date Time Suite

#include "CaramelTestPch.h"

#include <Caramel/DateTime/DateTime.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( DateTimeSuite )
{

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

    CHECK( true  == dt.TryParse( "1984/05/06 17:28:39" ));
    CHECK( dt == Date( 1984, 5, 6 ) + TimeOfDay( 17, 28, 39 ));


    /// From ISO String ///

    const auto dt1 = DateTime::FromString( "2013-04-05T18:09:30" );
    CHECK( dt1 == Date( 2013, 4, 5 ) + TimeOfDay( 18, 9, 30 ));

    DateTime dt2;

    CHECK( true == dt2.TryParse( "2014-03-15T08:23:14" ));
    CHECK( dt2 == Date( 2014, 3, 15 ) + TimeOfDay( 8, 23, 14 ));

    // You may omit seconds.
    const auto dt3 = DateTime::FromString( "2013-04-05T18:09" );
    CHECK( dt3 == Date( 2013, 4, 5 ) + TimeOfDay( 18, 9, 0 ));
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


TEST( DateTimeUtcTest )
{
    const auto now = DateTime::Now();
    const auto utcNow = DateTime::UtcNow();

    const auto localNow = DateTime::UtcToLocal( utcNow );

    CHECK_CLOSE( 0, ( localNow - now ).TotalSeconds(), 1 );
}


} // SUITE DateTimeSuite

} // namespace Caramel
