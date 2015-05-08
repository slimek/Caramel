// Caramel C++ Library Test - DateTime - Days Suite

#include "CaramelTestPch.h"

#include <Caramel/DateTime/Days.h>
#include <Caramel/DateTime/TimeSpan.h>


namespace Caramel
{

SUITE( Days )
{

TEST( Days )
{
    const Days d0;

    CHECK( Days( 0 ) == d0 );

    const Days d1( 42 );
    const Days d2( -90 );

    CHECK( 42  == d1.ToInt() );
    CHECK( -90 == d2.ToInt() );
}


TEST( DaysComparisons )
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


TEST( DaysArithmetic )
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


TEST( DaysTimeSpanArithmetic )
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


} // SUITE Days

} // namespace Caramel
