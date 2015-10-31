// Caramel C++ Library Test - Chrono - Clock Proxy Suite

#include "CaramelTestPch.h"

#include <Caramel/Chrono/ClockProxy.h>
#include <Caramel/Chrono/SecondClock.h>
#include <Caramel/Chrono/TickClock.h>
#include <thread>


namespace Caramel
{

SUITE( ClockProxy )
{

TEST( ClockProxy )
{
    /// Proxy of TickClock ///
    {
        ClockProxy clock = MakeClockProxy< TickClock >();

        const auto se1 = clock.SinceEpoch();
        const auto se2 = TickClock::Now().time_since_epoch();

        //CHECK_CLOSE( se1, se2, Ticks( 10 ));
    }


    /// Proxy of SecondClock ///
    {
        ClockProxy clock = MakeClockProxy< SecondClock >();

        const auto se1 = clock.SinceEpoch();
        const auto se2 = Ticks( SecondClock::Now().time_since_epoch() );

        //CHECK_CLOSE( se1, se2, Ticks( 10 ));
    }
}

//
// Custom Clock - It keeps still until you call Advance().
//
// REMARKS: In a more strict design, a custom clock should also has a custom time point.
//

class CustomClock
{
public:

    static SecondPoint Now() { return m_now; }

    static void Reset() { m_now = SecondClock::Now(); }
    static void Advance( Seconds s ) { m_now += s; }

private:
    static SecondPoint m_now;
};

SecondPoint CustomClock::m_now;


TEST( ClockProxyOfCustomClock )
{
    CustomClock::Reset();

    ClockProxy clock = MakeClockProxy< CustomClock >();

    const auto pnow1 = clock.SinceEpoch();
    const auto cnow1 = CustomClock::Now();

    CHECK( pnow1 == Ticks( cnow1.time_since_epoch() ));

    std::this_thread::sleep_for( std::chrono::seconds( 1 ));


    // Custom Clock keep still, as well as the clock proxy.

    const auto pnow2 = clock.SinceEpoch();
    CHECK( pnow2 == pnow1 );

        
    // If Custom Clock advanced, the clock proxy also did.

    CustomClock::Advance( Seconds( 1 ));

    const auto pnow3 = clock.SinceEpoch();
    //CHECK_CLOSE( Ticks( 1000 ), pnow3 - pnow2, Ticks( 1 ));
}

} // SUITE ClockProxy

} // namespace Caramel
