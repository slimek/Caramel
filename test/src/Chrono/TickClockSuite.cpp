// Caramel C++ Library Test - Chrono - Tick Clock Suite

#include "CaramelTestPch.h"

#include <Caramel/Chrono/TickClock.h>
#include <thread>


namespace Caramel
{

SUITE( TickClock )
{

TEST( TickClock )
{
    const TickPoint now1 = TickClock::Now();
    TickWatch watch;

    std::this_thread::sleep_for( std::chrono::seconds( 1 ));

    const TickPoint now2 = TickClock::Now();
    const Ticks delta = now2 - now1;
    
    CHECK_CLOSE( 1000, delta.ToNumber(), 50 );

    const Ticks elapsed = watch.Elapsed();
    const Ticks slice   = watch.Slice();
    const Ticks reseted = watch.Elapsed();

    CHECK_CLOSE( Ticks( 1000 ), elapsed, Ticks( 50 ));
    CHECK_CLOSE( Ticks( 1000 ), slice,   Ticks( 50 ));
    CHECK_CLOSE( Ticks( 0 ),    reseted, Ticks( 50 ));


    /// Default Values of Ticks ///

    const Ticks dur0;
    CHECK( 0 == dur0.ToInt64() );


    /// Numeric Convertible ///

    const Ticks t42( 42 );
    CHECK( "42" == Format( "{0}", t42 ));
}


} // SUITE TickClock

} // namespace Caramel
