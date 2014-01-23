// Caramel C++ Library Test - Task - Worker Thread Test

#include "CaramelTestPch.h"

#include <Caramel/Async/WaitableBool.h>
#include <Caramel/String/Format.h>
#include <Caramel/Task/WorkerThread.h>
#include <UnitTest++/UnitTest++.h>
#include <algorithm>
#include <atomic>
#include <deque>
#include <random>
#include <vector>


namespace Caramel
{

SUITE( WorkerThreadSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Worker Thread Test
//

TEST( WorkerThreadTrivialTest )
{
    WorkerThread worker( "Trivial" );
    worker.Stop();
}


TEST( WorkerThreadNormalTest )
{
    WorkerThread worker( "Normal" );

    WaitableBool ready( false );


    /// Execute One Task ///

    Bool flag1 = false;

    worker.Submit( Task( "Flag1", [&]
    {
        flag1 = true;
        ready = true;
    }));

    ready.Wait();

    CHECK( true == flag1 );


    /// Execute Many Tasks - Try 100 times ///

    for ( Uint i = 0; i < 100; ++ i )
    {
        std::atomic< Int > counter( 0 );

        for ( Uint j = 0; j < 100; ++ j )
        {
            worker.Submit( Task( "Counter", [&]
            {
                ++ counter;
            }));
        }

        ready = false;
        worker.Submit( Task( "End", [&] { ready = true; } ));
    
        ready.Wait();

        CHECK( 100 == counter.load() );
    }

    worker.Stop();
}


TEST( WorkerThreadDelayTest )
{
    WorkerThread worker( "Delay" );

    /// One Delay Tasks ///

    {
        WaitableBool slowReady( false );
        WaitableBool fastReady( false );

        Task slowTask( "Slow", [&] { slowReady = true; } );
        slowTask.DelayFor( Ticks( 100 ));

        Task fastTask( "Fast", [&] { fastReady = true; } );

        TickClock clock;

        worker.Submit( slowTask );
        worker.Submit( fastTask );

        fastReady.Wait();

        CHECK( false == slowReady );

        slowReady.Wait();

        CHECK_CLOSE( Ticks( 110 ), clock.Slice(), Ticks( 10 ));
    }


    /// Many Delay Tasks - Try 10 Times ///

    std::random_device rd;
    std::mt19937 rand( rd() );

    for ( Uint lp = 0; lp < 10; ++ lp )
    {
        std::deque< Int > ilist;
        WaitableBool ready( false );

        Int n = 0;
        std::vector< Int > ivals( 10 );
        std::generate( ivals.begin(), ivals.end(), [&] { return n++; } );

        std::shuffle( ivals.begin(), ivals.end(), rand );

        std::vector< Int > answer( 10 );
        for ( Uint i = 0; i < ivals.size(); ++ i )
        {
            answer[ ivals[i] ] = i;
        }

        // Submit tasks with different delays, in shuffled order.

        for ( Uint i = 0; i < ivals.size(); ++ i )
        {
            const Int value = ivals[i];

            worker.Submit(
                MakeTask(
                    Format( "Delay{0}", i ),
                    [i,value,&ilist] { ilist.push_back( i ); }
                )
                .DelayFor( Ticks( 10 * value ))
            );
        }

        worker.Submit( MakeTask( "End", [&] { ready = true; } ).DelayFor( Ticks( 120 )));        

        ready.Wait();

        CHECK( true == std::equal( ilist.begin(), ilist.end(), answer.begin() ));
    }

    worker.Stop();
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE WorkerThreadSuite

} // namespace Caramel
