// Caramel C++ Library Test - Concurrent - Delay Queue Suite

#include "CaramelTestPch.h"

#include <Caramel/Concurrent/DelayQueue.h>
#include <Caramel/Thread/ThisThread.h>


namespace Caramel
{

SUITE( ConcurrentDelayQueue )
{

TEST( ConcurrentDelayQueue )
{
    Concurrent::DelayQueue< Int > que( Seconds( 0.4 ));

    CHECK( true == que.IsEmpty() );

    const Int v = 7;
    que.Push( v );  // l-value
    que.Push( 42 ); // r-value

    CHECK( false == que.IsEmpty() );

    Int value = 0;

    // Should not expired yet.
    CHECK( false == que.TryPop( value ));

    ThisThread::SleepFor( Seconds( 0.5 ));

    CHECK( true == que.TryPop( value ));
    CHECK( 7 == value );

    CHECK( true == que.TryPop( value ));
    CHECK( 42 == value );

    CHECK( false == que.TryPop( value ));
    CHECK( que.IsEmpty() );
}

} // SUITE ConcurrentDelayQueue

} // namespace Caramel
