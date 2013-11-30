// Caramel C++ Library Test - Async - Timed Boolean Test

#include "CaramelTestPch.h"

#include <Caramel/Async/TimedBool.h>
#include <Caramel/Chrono/SecondClock.h>
#include <Caramel/Chrono/TickClock.h>
#include <UnitTest++/UnitTest++.h>
#include <thread>


namespace Caramel
{

SUITE( TimedBoolSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Timed Boolean Test
//

TEST( TickedBoolTest )
{
    typedef TimedBool< TickClock > TickedBool;

    TickedBool tb1;
    TickedBool tb2( Ticks( 90 ));
    TickedBool tb3( Ticks( 90 ));
    TickedBool tb4( Seconds( 0.09 ));

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


    /// Immediately Expires ///

    TickedBool tb5( Ticks::Zero() );
    CHECK( true == tb5 );


    /// Never Expires ///

    TickedBool tb6( Ticks::MaxValue() );
    CHECK( false == tb6 );


    /// Boolean Conversions ///

    CHECK( true == tb5.ToBool() );
    CHECK( true == tb5.IsExpired() );

    CHECK( false == tb6.ToBool() );
    CHECK( false == tb6.IsExpired() );


    /// Start and Continue ///

    TickedBool tb7;
    TickedBool tb8;

    tb7.Start( Seconds( 0.06 ));
    tb8.Start( Ticks( 60 ));

    std::this_thread::sleep_for( std::chrono::milliseconds( 100 ));

    CHECK( true == tb7 );
    CHECK( true == tb8 );

    tb7.Restart();
    tb8.Continue();

    std::this_thread::sleep_for( std::chrono::milliseconds( 40 ));

    CHECK( false == tb7 );
    CHECK( true == tb8 );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE TimedBoolSuite

} // namespace Caramel
