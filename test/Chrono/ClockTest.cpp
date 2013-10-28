// Caramel C++ Library Test - Chrono - Clock Test

#include "CaramelTestPch.h"

#include <Caramel/Chrono/SecondClock.h>
#include <Caramel/Chrono/TickClock.h>
#include <UnitTest++/UnitTest++.h>
#include <thread>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Tick Clock Test
//

TEST( TickClockTest )
{
    const TickPoint now1 = TickClock::Now();
    TickClock clock;

    std::this_thread::sleep_for( std::chrono::seconds( 1 ));

    const TickPoint now2 = TickClock::Now();
    const Ticks delta = now2 - now1;
    
    CHECK_CLOSE( 1000, delta.ToNumber(), 50 );

    const Ticks elapsed = clock.Elapsed();
    const Ticks slice   = clock.Slice();
    const Ticks reseted = clock.Elapsed();

    CHECK_CLOSE( Ticks( 1000 ), elapsed, Ticks( 50 ));
    CHECK_CLOSE( Ticks( 1000 ), slice,   Ticks( 50 ));
    CHECK_CLOSE( Ticks( 0 ),    reseted, Ticks( 50 ));
    
    CARAMEL_TRACE_DEBUG( "Duration: %d", delta.ToInt32() );


    /// Default Values of Ticks ///

    const Ticks dur0;
    CHECK( 0 == dur0.ToInt64() );
}


///////////////////////////////////////////////////////////////////////////////
//
// Second Clock Test
//

TEST( SecondClockTest )
{
    const SecondPoint now1 = SecondClock::Now();
    SecondClock clock;

    std::this_thread::sleep_for( std::chrono::seconds( 1 ));

    const SecondPoint now2 = SecondClock::Now();
    const Seconds delta = now2 - now1;
    
    CHECK_CLOSE( 1.0, delta.ToNumber(), 0.05 );

    const Seconds elapsed = clock.Elapsed();
    const Seconds slice   = clock.Slice();
    const Seconds reseted = clock.Elapsed();

    CHECK_CLOSE( Seconds( 1 ), elapsed, Seconds( 0.05 ));
    CHECK_CLOSE( Seconds( 1 ), slice,   Seconds( 0.05 ));
    CHECK_CLOSE( Seconds( 0 ), reseted, Seconds( 0.05 ));
    
    CARAMEL_TRACE_DEBUG( "Duration: %f", delta );

    const Seconds sinceEpoch = SecondClock::SinceEpoch();

    CARAMEL_TRACE_DEBUG( "Since Epoch seconds: %f", sinceEpoch );
}


///////////////////////////////////////////////////////////////////////////////
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
}

///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel