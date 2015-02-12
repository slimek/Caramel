// Caramel C++ Library Test - Concurrent - Stack Suite

#include "CaramelTestPch.h"

#include <Caramel/Chrono/TimedBool.h>
#include <Caramel/Concurrent/Stack.h>
#include <Caramel/Thread/Thread.h>
#include <atomic>


namespace Caramel
{

SUITE( ConcurrentStackSuite )
{

TEST( ConcurrentStackTest )
{
    Concurrent::Stack< Int > istack;
    Int value = 0;

    /// Trivial ///

    CHECK( true  == istack.IsEmpty() );
    CHECK( 0     == istack.Size() );
    CHECK( false == istack.TryPop( value ));


    /// Push and Pop 1 values ///

    istack.Push( 42 );

    CHECK( false == istack.IsEmpty() );
    CHECK( 1     == istack.Size() );
    CHECK( true  == istack.TryPop( value ));
    CHECK( 42    == value );

    CHECK( true  == istack.IsEmpty() );
    CHECK( 0     == istack.Size() );
    CHECK( false == istack.TryPop( value ));


    /// Push and Pop a sequence ///

    istack.Push( 16 );
    istack.Push( 64 );
    istack.Push( 256 );

    CHECK( false == istack.IsEmpty() );
    CHECK( 3     == istack.Size() );

    CHECK( true  == istack.TryPop( value ));
    CHECK( 256   == value );
    CHECK( true  == istack.TryPop( value ));
    CHECK( 64    == value );
    CHECK( true  == istack.TryPop( value ));
    CHECK( 16    == value );
    CHECK( false == istack.TryPop( value ));
}


TEST( ConcurrentStackWarmupTest )
{
    Concurrent::Stack< std::string > stack;

    TimedBool< TickClock > timeup( 1000 );

    std::atomic< Int > pushes( 0 );
    std::atomic< Int > pops( 0 );

    Thread t1( "Pusher",
    [&]
    {
        while ( ! timeup )
        {
            stack.Push( "Cirno" );
            ++ pushes;
        }
    });

    Thread t2( "Popper",
    [&]
    {
        while ( ! timeup )
        {
            std::string value;
            if ( stack.TryPop( value ))
            {
                ++ pops;
            }
        }
    });

    t1.Join();
    t2.Join();

    CARAMEL_TRACE_DEBUG( "Pushes: %d, Pops: %d", pushes.load(), pops.load() );
}


} // SUITE ConcurrentStackSuite

} // namespace Caramel
