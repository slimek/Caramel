// Caramel C++ Library Test - Concurrent - Blocking Queue Test

#include "CaramelTestPch.h"

#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Concurrent/BlockingQueue.h>
#include <Caramel/Thread/ThisThread.h>
#include <UnitTest++/UnitTest++.h>
#include <future>


namespace Caramel
{

SUITE( ConcurrentBlockingQueueSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Concurrent Blocking Queue Test
//

TEST( BlockingQueueBasicTest )
{
    /// Int Queue ///

    {
        Concurrent::BlockingQueue< Int > iqueue;

        Int value = 0;

        CHECK( true  == iqueue.IsEmpty() );
        CHECK( false == iqueue.PopOrWaitFor( value, Ticks( 0 )));

        iqueue.Push( 42 );

        CHECK( false == iqueue.IsEmpty() );
        CHECK( true  == iqueue.PopOrWaitFor( value, Ticks( 0 )));
        CHECK( 42    == value );

        TickClock clock;
    
        CHECK( false == iqueue.PopOrWaitFor( value, Ticks( 100 )));
        CHECK( Ticks( 80 ) <= clock.Slice() );

        
        // Pulse All

        std::async( std::launch::async, [&]
        {
            ThisThread::SleepFor( Ticks( 100 ));
            iqueue.PulseAll();
        });

        iqueue.PopOrWaitFor( value, Ticks( 500 ));

        CHECK( Ticks( 200 ) > clock.Slice() );


        // Wait and Available

        std::async( std::launch::async, [&]
        {
            ThisThread::SleepFor( Ticks( 100 ));
            iqueue.Push( 125 );
        });

        CHECK( false == iqueue.PopOrWaitFor( value, Ticks( 0 )));
        CHECK( true  == iqueue.PopOrWaitFor( value, Ticks( 200 )));
        CHECK( 125   == value );

        CHECK( true == iqueue.IsEmpty() );
    }

    
    /// String Queue ///

    {
        Concurrent::BlockingQueue< std::string > squeue;

        const std::string reimu( "Reimu" );
        std::string value;

        squeue.Push( reimu );    // Lvalue
        squeue.Push( "Alice" );  // Rvalue

        CHECK( true    == squeue.PopOrWaitFor( value, Ticks( 10 )));
        CHECK( "Reimu" == value );
        CHECK( true    == squeue.PopOrWaitFor( value, Ticks( 10 )));
        CHECK( "Alice" == value );
        CHECK( false   == squeue.PopOrWaitFor( value, Ticks( 10 )));
    }
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE ConcurrentBlockingQueueSuite

} // namespace Caramel
