// Caramel C++ Library Test - DateTime - Time of Day Suite

#include "CaramelTestPch.h"

#include <Caramel/DateTime/DateTime.h>
#include <Caramel/DateTime/TimeOfDay.h>


namespace Caramel
{

SUITE( TimeOfDaySuite )
{

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
    CHECK( 0 == zero.Millisecond() );

    const auto tod1 = TimeOfDay::FromString( "12:34:56" );

    CHECK( "12:34:56" == tod1.ToString() );
    CHECK( TimeOfDay( 12, 34, 56 ) == tod1 );
    CHECK( 12 == tod1.Hour() );
    CHECK( 34 == tod1.Minute() );
    CHECK( 56 == tod1.Second() );

    CHECK( "23:59:59" == TimeOfDay::FromString( "23:59:59" ).ToString() );


    /// Invalid Values ///

    // Time of Day can be longer than a day
    CHECK_THROW( TimeOfDay( 24, 0, 0 ), Exception );
    CHECK_THROW( TimeOfDay::FromString( "24:00:00" ), Exception );

    // Time of Day can not be negative.
    CHECK_THROW( TimeOfDay( -1, 30, 15 ), Exception );
    CHECK_THROW( TimeOfDay::FromString( "-01:30:15" ), Exception );


    /// Format String ///

    CHECK( "12:34:56" == tod1.Format( "%H:%M:%S" ));
    CHECK( "12:34"    == tod1.Format( "%H:%M" ));


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

    
    /// With Fractional ///

    const auto tod3 = TimeOfDay::FromString( "12:34:56.785" );
    CHECK( tod3.Millisecond() == 785 );

    const auto tod4 = TimeOfDay::FromString( "12:34:56.125385" );
    CHECK( tod4.Millisecond() == 125 );

    const auto dt2 = DateTime::FromString( "2013-04-05 16:27:38.235" );
    CHECK( 235 == dt2.TimeOfDay().Millisecond() );
}


} // SUITE TimeOfDaySuite

} // namespace Caramel
