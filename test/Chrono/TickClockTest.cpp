// Caramel C++ Library Test - Chrono - Tick Clock Test

#include "CaramelTestPch.h"

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

    std::this_thread::sleep_for( std::chrono::seconds( 1 ));

    const TickPoint now2 = TickClock::Now();

    const TickDuration delta = now2 - now1;

    CHECK( 1000 <= delta.ToNumber() );
    
    CARAMEL_TRACE_DEBUG( "Duration: %d", delta.ToInt32() );
}

///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel