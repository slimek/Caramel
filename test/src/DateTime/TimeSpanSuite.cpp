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
        CHECK( 0 == time0.Milliseconds() );

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

        // Nagative TimeSpan

        const auto time5 = - Minutes( 30 );

        CHECK( 0 == time5.Days() );
        CHECK( 0 == time5.Hours() );
        CHECK( -30 == time5.Minutes() );
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


        /// Seconds with Fractional ///

        const TimeSpan time3 = Seconds( 0.5 );

        CHECK( 0 == time3.Seconds() );
        CHECK( 500 == time3.Milliseconds() );
        CHECK( "00:00:00.500000" == time3.ToString() );
          // TODO: How to reduce the digits of the fractional part?

        const TimeSpan time4 = Milliseconds( 1350 );

        CHECK( 1 == time4.Seconds() );
        CHECK( 350 == time4.Milliseconds() );
        CHECK( "00:00:01.350000" == time4.ToString() );

        const Seconds secs3 = time4;
        
        CHECK( Seconds( 1.35 ) == secs3 );

        // The part less than milliseconds is dropped.
        const TimeSpan time5 = Seconds( - 35.6125 );

        CHECK( -35 == time5.Seconds() );
        CHECK( -612 == time5.Milliseconds() );
        CHECK( "-00:00:35.612000" == time5.ToString() );
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
        CHECK( -29 == t4.Minutes() );
        CHECK( -18 == t4.Seconds() );

        CHECK( Seconds( 42 ) == t1 );  // t1 should not be modified

        const TimeSpan t5 = Hours( 6 ) + Minutes( 49 ) - Seconds( 36 );

        CHECK( TimeSpan( 6, 48, 24 ) == t5 );

        
        /// Operation with Days ///
           
        const TimeSpan h12( 12, 0, 0 );
        const auto d2h12 = h12 + Days( 2 );
        const auto d1h12 = d2h12 - Days( 1 );

        CHECK( TimeSpan( 60, 0, 0 ) == d2h12 );
        CHECK( TimeSpan( 36, 0, 0 ) == d1h12 );

        const auto d2 = Days::Truncate( d2h12 );

        CHECK( Days( 2 ) == d2 );
    }
}


TEST( TimeSpanLimitTest )
{
    const auto max = TimeSpan::MaxValue();
    const auto min = TimeSpan::MinValue();

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


TEST( TimeSpanTryParseTest )
{
    TimeSpan span;

    CHECK( false == span.TryParse( "" ));           // empty string
    CHECK( false == span.TryParse( "Zeit" ));       // not a time span
    
    CHECK( true == span.TryParse( "12" ));          // 1 int is hours
    CHECK( Hours( 12 ) == span );

    CHECK( true == span.TryParse( "12:34" ));       // 2 ints are hh:mm
    CHECK( TimeSpan( 12, 34, 0 ) == span );

    CHECK( true == span.TryParse( "12:34:56" ));    // 3 ints are hh:mm:ss
    CHECK( TimeSpan( 12, 34, 56 ) == span );

    CHECK( true == span.TryParse( "12:34:78" ));    // components would automatically carry in.
    CHECK( TimeSpan( 12, 35, 18 ) == span );

    //
    // With fractional part
    // - Both '.' and ',' are acceptable.
    //

    CHECK( true == span.TryParse( "12:34:56.78" ));
    CHECK( TimeSpan( 12, 34, 56 ) + Seconds( 0.78 ) == span );

    CHECK( true == span.TryParse( "12:34:56,78" ));
    CHECK( TimeSpan( 12, 34, 56 ) + Seconds( 0.78 ) == span );
}


TEST( TimeSpanFormatTest )
{
    const TimeSpan t0;
    const TimeSpan t1( 12, 34, 56 );
    const TimeSpan t2 = Days( 2 ) + Minutes( 42 );
    const TimeSpan t3 = Seconds( 35.125 );

    CHECK( "00:00:00"  == t0.Format( "%H:%M:%S" ));
    CHECK( "12:34:56"  == t1.Format( "%H:%M:%S" ));
    CHECK( "48h42m"    == t2.Format( "%Hh%Mm" ));
    CHECK( "35.125000" == t3.Format( "%S.%f" ));

    // TODO: There are no easy way to format the days part?
    CHECK( 0 == t2.Hours() );
    CHECK( 2 == t2.Days() );
    // CHECK( "02d00h42m" == t2.FormatEx( ??? ));
}


} // SUITE TimeSpanSuite

} // namespace Caramel
