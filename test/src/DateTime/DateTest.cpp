// Caramel C++ Library Test - DateTime - Date Test

#include "CaramelTestPch.h"

#include <Caramel/DateTime/Date.h>
#include <Caramel/DateTime/Days.h>
#include <Caramel/DateTime/TimeSpan.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( DateSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Date Test
//

TEST( DateTest )
{
    const Date notDate;
    const Date today = Date::Today();

    CHECK( false == notDate.IsValid() );
    CHECK( true  == today.IsValid() );

    const Date d1( 2013, 4, 5 );

    CHECK( 2013 == d1.Year() );
    CHECK( 4    == d1.Month() );
    CHECK( 5    == d1.Day() );
}


TEST( DateComparisonTest )
{
    const auto d1 = Date::FromString( "1987-06-23" );
    const auto d2 = Date::FromString( "2013-04-05" );

    CHECK( d1 != d2 );
    CHECK( d1 <  d2 );
    CHECK( d1 <= d2 );
    CHECK( false == ( d1 == d2 ));
    CHECK( false == ( d1 >  d2 ));
    CHECK( false == ( d1 >= d2 ));

    const auto d3 = d1;

    CHECK( d1 == d3 );
    CHECK( d1 <= d3 );
    CHECK( d1 >= d3 );
    CHECK( false == ( d1 != d3 ));
    CHECK( false == ( d1 <  d3 ));
    CHECK( false == ( d1 >  d3 ));
}


TEST( DateStringTest )
{
    const auto d1 = Date::FromString( "2013-04-05" );

    CHECK( 2013 == d1.Year() );
    CHECK( 4    == d1.Month() );
    CHECK( 5    == d1.Day() );

    CHECK( "2013-04-05" == d1.ToString() );

    const auto d2 = Date::FromString( "2013-4-5" );

    CHECK( d1 == d2 );

    const auto d3 = Date::FromString( "2013/04/05" );

    CHECK( d1 == d3 );
}


TEST( DateFormatTest )
{
    const auto d1 = Date::FromString( "2013-04-05" );

    CHECK( "2013/04/05" == d1.Format( "%Y/%m/%d" ));
    CHECK( "Apr 05 13" == d1.Format( "%b %d %y" ));
}


TEST( DateMacroTest )
{
    const auto dm = Date::FromMacro( __DATE__ );

    CARAMEL_TRACE_DEBUG( "Build date: %s", dm.ToString() );

    CHECK( Date::Today() >= dm );
}


TEST( DaysTest )
{
    const Days d0;

    CHECK( Days( 0 ) == d0 );

    const Days d1( 42 );
    const Days d2( -90 );

    CHECK( 42  == d1.ToInt() );
    CHECK( -90 == d2.ToInt() );
}


TEST( DaysComparisonTest )
{
    const Days d1( 1 );
    const Days d2( 42 );

    CHECK( d1 <  d2 );
    CHECK( d1 <= d2 );
    CHECK( d1 != d2 );
    CHECK( false == ( d1 >  d2 ));
    CHECK( false == ( d1 >= d2 ));
    CHECK( false == ( d1 == d2 ));

    const Days d3 = d1;

    CHECK( d1 <= d3 );
    CHECK( d1 >= d3 );
    CHECK( d1 == d3 );
    CHECK( false == ( d1 <  d3 ));
    CHECK( false == ( d1 >  d3 ));
    CHECK( false == ( d1 != d3 ));
}


TEST( DaysArithmeticTest )
{
    const Days d1( 42 );
    const Days d2( 3 );

    CHECK( Days( 45 ) == d1 + d2 );
    CHECK( Days( 39 ) == d1 - d2 );

    const Days dz;

    CHECK( d1 == d1 + dz );
    CHECK( d1 == d1 - dz );

    // Binary operators should not change d1's value.
    CHECK( Days( 42 ) == d1 );


    /// Self Operators ///

    Days d3( 18 );

    d3 += Days( 5 );
    CHECK( Days( 23 ) == d3 );

    d3 -= Days( 9 );
    CHECK( Days( 14 ) == d3 );
}


TEST( DateDaysArithmeticTest )
{
    const Date d1( 1987, 6, 5 );
    
    CHECK( Date( 1987, 7, 4 ) == d1 + Days( 29 ));
    CHECK( Date( 1987, 6, 4 ) == d1 - Days( 1 ));

    const Days dz;

    CHECK( d1 == d1 + dz );
    CHECK( d1 == d1 - dz );

    // Binary operators should not change d1's value.
    CHECK( Date( 1987, 6, 5 ) == d1 );


    /// Test Leap Year ///

    const Date d2( 2003, 2, 27 );
    const Date d3( 2004, 2, 27 );

    CHECK( Date( 2003, 3, 2 ) == d2 + Days( 3 ));
    CHECK( Date( 2004, 3, 1 ) == d3 + Days( 3 ));


    /// Self Operators ///

    Date d4( 2013, 4, 5 );

    d4 += Days( 3 );
    CHECK( Date( 2013, 4, 8 ) == d4 );

    d4 -= Days( 8 );
    CHECK( Date( 2013, 3, 31 ) == d4 );


    /// Difference of Dates ///

    const Date d5( 2013, 5, 6 );

    CHECK( Days( 0 )   == d4 - d4 );
    CHECK( Days( 365 ) == d3 - d2 );
    CHECK( Days( -36 ) == d4 - d5 );  // d4 now is 2013/3/31

    // Binary operators should not change d4's value.
    CHECK( Date( 2013, 3, 31 ) == d4 );
}


TEST( DaysTimeSpanTest )
{
    const Days d0( 0 );
    const TimeSpan t0 = d0;

    CHECK( 0 == t0.TotalSeconds() );

    CHECK( Hours( 24 ) == Days( 1 ));
    CHECK( Hours( -72 ) == Days( -3 ));


    /// Overflow ///

    TimeSpan dummy;

    const auto dmax = Days::MaxValue();

    CHECK_THROW( dummy = static_cast< TimeSpan >( dmax ), Caramel::Exception );

    const Days dupper( INT_MAX / 24 );

    CHECK( Hours( ( INT_MAX / 24 ) * 24 ) == dupper );
    CHECK_THROW( dummy = static_cast< TimeSpan >( dupper + Days( 1 )), Caramel::Exception );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE DateSuite

} // namespace Caramel
