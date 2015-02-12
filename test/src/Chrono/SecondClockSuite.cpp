// Caramel C++ Library Test - Chrono - Second Clock Suite

#include "CaramelTestPch.h"

#include <Caramel/Chrono/SecondClock.h>
#include <Caramel/Chrono/TickClock.h>
#include <thread>


namespace Caramel
{

SUITE( SecondClockSuite )
{

TEST( SecondClockTest )
{
    const SecondPoint now1 = SecondClock::Now();
    SecondWatch watch;

    std::this_thread::sleep_for( std::chrono::seconds( 1 ));

    const SecondPoint now2 = SecondClock::Now();
    const Seconds delta = now2 - now1;
    
    CHECK_CLOSE( 1.0, delta.ToNumber(), 0.05 );

    const Seconds elapsed = watch.Elapsed();
    const Seconds slice   = watch.Slice();
    const Seconds reseted = watch.Elapsed();

    CHECK_CLOSE( Seconds( 1 ), elapsed, Seconds( 0.05 ));
    CHECK_CLOSE( Seconds( 1 ), slice,   Seconds( 0.05 ));
    CHECK_CLOSE( Seconds( 0 ), reseted, Seconds( 0.05 ));
    
    CARAMEL_TRACE_DEBUG( "Duration: %f", delta );
}


TEST( SecondsDivideTest )
{
    /// Operators ///
    {
        const Seconds n1( 8.5 );
        const Seconds d1( 2.0 );

        CHECK( 4.25            == n1 / d1 );
        CHECK( Seconds( 4.25 ) == n1 / 2 );
        CHECK( Seconds( 0.5 )  == n1 % d1 );


        const Seconds n2( 4218 );
        const Seconds d2( 60 );

        CHECK( 70.3          == n2 / d2 );
        CHECK( Seconds( 18 ) == n2 % d2 );


        const Seconds n3( 9313 );
        const Seconds d3( 67 );

        CHECK( 139             == n3 / d3 );
        CHECK( Seconds::Zero() == n3 % d3 );
    }

    /// Divide By ///
    {
        const Seconds n1( 8.5 );
        const Seconds d1( 2.0 );

        const auto r1 = n1.DivideBy( d1 );

        CHECK( 4 == r1.quotient );
        CHECK( Seconds( 0.5 ) == r1.remainder );


        const Seconds n2( 4218 );
        const Seconds d2( 60 );

        const auto r2 = n2.DivideBy( d2 );

        CHECK( 70 == r2.quotient );
        CHECK( Seconds( 18 ) == r2.remainder );


        const Seconds n3( 9313 );
        const Seconds d3( 67 );

        const auto r3 = n3.DivideBy( d3 );

        CHECK( 139 == r3.quotient );
        CHECK( Seconds::Zero() == r3.remainder );
    }
}


//
// Duration Conversion
//

TEST( DurationConvertTest )
{
    const Ticks   tz( 0 );
    const Seconds sz( 0 );

    CHECK( tz == sz );


    const Ticks   tu( 1000 );
    const Seconds su( 1.0 );

    CHECK( tu == su );

    const Ticks tdur = su;

    CHECK( 1000 == tdur.ToNumber() );

    const Seconds sdur = tu;

    CHECK( 1.0 == sdur.ToNumber() );


    /// Truncation ///

    Seconds s1( 1.5 );

    CHECK( Seconds( 1.0 ) == Seconds::TruncFrom( s1 ));
    s1.Trunc();
    CHECK( Seconds( 1.0 ) == s1 );

    Seconds s2( -1.5 );

    CHECK( Seconds( -1.0 ) == Seconds::TruncFrom( s2 ));
    s2.Trunc();
    CHECK( Seconds( -1.0 ) == s2 );

    Seconds s3( 125 );

    CHECK( Seconds( 125 ) == Seconds::TruncFrom( s3 ));
}


} // SUITE ClockSuite

} // namespace Caramel
