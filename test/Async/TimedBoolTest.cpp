// Caramel C++ Library Test - Async - Timed Boolean Test

#include "CaramelTestPch.h"

#include <Caramel/Async/TimedBool.h>
#include <Caramel/Chrono/SecondClock.h>
#include <UnitTest++/UnitTest++.h>
#include <thread>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Timed Boolean Test
//

TEST( TimedBoolTest )
{
    TimedBool tb1;
    TimedBool tb2( Ticks( 90 ));
    TimedBool tb3( Ticks( 90 ));
    TimedBool tb4( Seconds( 0.09 ));

    CHECK( false == tb1 );
    CHECK( false == tb2 );
    CHECK( false == tb3 );
    CHECK( false == tb4 );

    std::this_thread::sleep_for( std::chrono::milliseconds( 50 ));

    tb2.ExpireNow();

    CHECK( true == tb2 );

    std::this_thread::sleep_for( std::chrono::milliseconds( 50 ));

    CHECK( true == tb3 );
    CHECK( true == tb4 );

    std::this_thread::sleep_for( std::chrono::milliseconds( 50 ));

    tb3.Continue();
    tb4.Restart();

    std::this_thread::sleep_for( std::chrono::milliseconds( 50 ));
    
    CHECK( true  == tb3 );
    CHECK( false == tb4 );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
