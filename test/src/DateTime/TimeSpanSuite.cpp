// Caramel C++ Library Test - DateTime - Time Span Suite

#include "CaramelTestPch.h"

#include <Caramel/DateTime/DateTime.h>
#include <Caramel/DateTime/Days.h>
#include <Caramel/DateTime/TimeSpan.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( TimeSpanSuite )
{

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

        const TimeSpan t5 = Hours( 6 ) + Minutes( 49 ) - Seconds( 36 );

        CHECK( TimeSpan( 6, 48, 24 ) == t5 );
    }
}


TEST( TimeSpanLimitTest )
{
    const auto max = TimeSpan::MaxValue();
    const auto min = TimeSpan::MinValue();

    const double v = max.TotalHours();

    CHECK(  9223372036854.7754 == max.TotalSeconds() );
    CHECK( -9223372036854.7754 == min.TotalSeconds() );

    CHECK(  153722867280.91293 == max.TotalMinutes() );
    CHECK( -153722867280.91293 == min.TotalMinutes() );

    CHECK_CLOSE(  2562047788.0152, max.TotalHours(), 0.001 );
    CHECK_CLOSE( -2562047788.0152, min.TotalHours(), 0.001 );

    CHECK_CLOSE(  106751991.167, max.TotalDays(), 0.001 );
    CHECK_CLOSE( -106751991.167, min.TotalDays(), 0.001 );

    
    /// Overflow ///

    const auto overMax = max + Seconds( 1 );
    const auto overMin = min - Seconds( 1 );

    CHECK( min < overMax && overMax < min + Seconds( 1 ) );
    CHECK( max - Seconds( 1 ) < overMin && overMin < max );

}


TEST( LargeDateTimeDifferenceTest )
{
    const auto min    = DateTime::MinValue();
    const auto modern = DateTime::FromString( "2100-01-01 00:00" );

    const TimeSpan span = modern - min;

    CHECK( 22089888000.0 == span.TotalSeconds() );
    CHECK(   368164800.0 == span.TotalMinutes() );
    CHECK(     6136080.0 == span.TotalHours() );
    CHECK(      255670.0 == span.TotalDays() );
    
    CHECK( 255670 == span.Days() );
    CHECK(      0 == span.Hours() );
    CHECK(      0 == span.Minutes() );
    CHECK(      0 == span.Seconds() );


    const auto max = DateTime::MaxValue();  // 9999-12-31 23:59:59.999999
    const TimeSpan span2 = max - min;

    CHECK( 271389744000.0 == span2.TotalSeconds() );
    CHECK(   4523162400.0 == span2.TotalMinutes() );
    CHECK(     75386040.0 == span2.TotalHours() );
    CHECK(      3141085.0 == span2.TotalDays() );

    CHECK( 3141084 == span2.Days() );
    CHECK(      23 == span2.Hours() );
    CHECK(      59 == span2.Minutes() );
    CHECK(      59 == span2.Seconds() );
}


} // SUITE TimeSpanSuite

} // namespace Caramel
