// Caramel C++ Library Test - Chrono - Timed Boolean Suite

#include "CaramelTestPch.h"

#include <Caramel/Chrono/TimedBool.h>
#include <Caramel/Chrono/SecondClock.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Thread/ThisThread.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( TimedBoolSuite )
{

TEST( TickedBoolTrivialTest )
{
    typedef TimedBool< TickClock > TickedBool;

    TickedBool tb( Ticks( 100 ));

    CHECK( Ticks( 100 ) == tb.GetDuration() );
    CHECK( TickClock::Now() < tb.GetDeadline() );
}


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

    ThisThread::SleepFor( Ticks( 50 ));

    tb2.ExpireNow();

    CHECK( true == tb2 );

    ThisThread::SleepFor( Ticks( 50 ));

    CHECK( true == tb3 );
    CHECK( true == tb4 );

    ThisThread::SleepFor( Ticks( 50 ));

    tb3.Continue();
    tb4.Restart();

    ThisThread::SleepFor( Ticks( 50 ));
    
    CHECK( true  == tb3 );
    CHECK( false == tb4 );


    /// Immediately Expires ///

    TickedBool tb5( Ticks::Zero() );
    CHECK( true == tb5 );


    /// Never Expires ///

    TickedBool tbMax( Ticks::MaxValue() );
    CHECK( false == tbMax );


    /// Boolean Conversions ///

    CHECK( true == tb5.ToBool() );
    CHECK( true == tb5.IsExpired() );

    CHECK( false == tbMax.ToBool() );
    CHECK( false == tbMax.IsExpired() );


    /// Start and Continue ///

    TickedBool tb7;
    TickedBool tb8;

    tb7.Start( Seconds( 0.06 ));
    tb8.Start( Ticks( 60 ));

    ThisThread::SleepFor( Ticks( 100 ));

    CHECK( true == tb7 );
    CHECK( true == tb8 );

    tb7.Restart();
    tb8.Continue();

    ThisThread::SleepFor( Ticks( 40 ));

    CHECK( false == tb7 );
    CHECK( true == tb8 );


    /// Take functions ///

    TickedBool tb9( Ticks( 40 ));

    ThisThread::SleepFor( Ticks( 50 ));

    CHECK( true  == tb9.TakeAndRestart() );
    CHECK( false == tb9 );

    ThisThread::SleepFor( Ticks( 60 ));

    CHECK( true  == tb9.TakeAndContinue() );
    CHECK( false == tb9 );

    ThisThread::SleepFor( Ticks( 30 ));

    CHECK( true == tb9 );


    // Yes, a TimeBool with MaxValue duration would never expire
    CHECK( false == tbMax );
}


TEST( SecondedBoolTest )
{
    typedef TimedBool< SecondClock > SecondedBool;

    SecondedBool sb1( 0.5 );
    SecondedBool sb2( 10 );

    CHECK( false == sb1 );
    CHECK( false == sb2 );

    ThisThread::SleepFor( Seconds( 0.6 ));

    CHECK( true  == sb1 );
    CHECK( false == sb2 );

    sb2.ExpireNow();

    CHECK( true == sb2 );
}


} // SUITE TimedBoolSuite

} // namespace Caramel
