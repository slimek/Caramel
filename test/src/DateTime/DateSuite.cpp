// Caramel C++ Library Test - DateTime - Date Suite

#include "CaramelTestPch.h"

#include <Caramel/DateTime/Date.h>
#include <Caramel/DateTime/Days.h>
#include <Caramel/DateTime/TimeSpan.h>


namespace Caramel
{

SUITE( Date )
{

TEST( Date )
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


TEST( DateComparison )
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


TEST( DateString )
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


TEST( DateFormat )
{
    const auto d1 = Date::FromString( "2013-04-05" );

    CHECK( "2013/04/05" == d1.Format( "%Y/%m/%d" ));
    CHECK( "Apr 05 13" == d1.Format( "%b %d %y" ));
}


TEST( DateTryParse )
{
    Date date;

    CHECK( false == date.TryParse( "" ));
    CHECK( false == date.TryParse( "Tag" ));

    CHECK( true == date.TryParse( "2013-04-05" ));
    CHECK( Date( 2013, 4, 5 ) == date );

    CHECK( true == date.TryParse( "1987/6/5" ));
    CHECK( Date( 1987, 6, 5 ) == date );
}


TEST( DateMacro )
{
    const auto dm = Date::FromMacro( __DATE__ );
    CHECK( Date::Today() >= dm );
}


TEST( DateDaysArithmetic )
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


} // SUITE Date

} // namespace Caramel
