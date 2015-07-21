// Caramel C++ Library Test - Concurrent - Blocking Queue Suite

#include "CaramelTestPch.h"

#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Concurrent/BlockingQueue.h>
#include <Caramel/Task/WorkerThread.h>
#include <Caramel/Thread/ThisThread.h>


namespace Caramel
{

SUITE( ConcurrentBlockingQueue )
{

TEST( BlockingQueueBasic )
{
    WorkerThread worker( "BlockingQueue" );

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

        TickWatch watch;
    
        CHECK( false == iqueue.PopOrWaitFor( value, Ticks( 100 )));
        CHECK( Ticks( 80 ) <= watch.Slice() );

        
        // Pulse All

        worker.Submit( MakeTask( "PulseAll", [&]
        {
            ThisThread::SleepFor( Ticks( 100 ));
            iqueue.PulseAll();
        }));

        CHECK( false == iqueue.PopOrWaitFor( value, Ticks( 500 )));
        CHECK( Ticks( 200 ) > watch.Slice() );


        // Wait and Available

        worker.Submit( MakeTask( "WaitAndAvailable",
        [&]
        {
            ThisThread::SleepFor( Ticks( 100 ));
            iqueue.Push( 125 );
        }));

        CHECK( false == iqueue.PopOrWaitFor( value, Ticks( 0 )));
        CHECK( true  == iqueue.PopOrWaitFor( value, Ticks( 200 )));
        CHECK( 125   == value );

        CHECK( true == iqueue.IsEmpty() );


        // Complete

        worker.Submit( MakeTask( "Complete",
        [&]
        {
            ThisThread::SleepFor( Ticks( 100 ));
            iqueue.Complete();
        }));

        CHECK( false == iqueue.PopOrWaitFor( value, Ticks( 200 )));
        
        watch.Reset();
        CHECK( false == iqueue.PopOrWaitFor( value, Ticks( 100 )));  // should return immediately
        CHECK_CLOSE( Ticks( 0 ), watch.Slice(), Ticks( 10 ));

        CHECK_THROW( iqueue.Push( 83 ), Caramel::Exception );
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
    
    
    /// Finalization ///
    
    worker.Stop();
}


TEST( ConcurrentBlockingQueueReset )
{
    Concurrent::BlockingQueue< Int > iqueue;
    Int value = 0;

    iqueue.Push( 42 );
    iqueue.Complete();

    // After Complete(), the queue throws if try to push.
    CHECK_THROW( iqueue.Push( 7 ), Caramel::Exception );

    // But after Reset(), the queue is re-usable.

    iqueue.Reset();
    iqueue.Push( 51 );

    CHECK( true == iqueue.PopOrWaitFor( value, Ticks( 1000 )));
    CHECK( 51 == value );
}


} // SUITE ConcurrentBlockingQueue

} // namespace Caramel
