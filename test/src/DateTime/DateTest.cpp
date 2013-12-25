// Caramel C++ Library Test - DateTime - Date Test

#include "CaramelTestPch.h"

#include <Caramel/DateTime/Date.h>
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
    CHECK( "20130405"   == d1.ToIsoString() );

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


///////////////////////////////////////////////////////////////////////////////

} // SUITE DateSuite

} // namespace Caramel
