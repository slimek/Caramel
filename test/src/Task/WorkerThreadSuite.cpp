// Caramel C++ Library Test - Task - Worker Thread Suite

#include "CaramelTestPch.h"

#include <Caramel/String/Format.h>
#include <Caramel/Task/WorkerThread.h>
#include <Caramel/Thread/WaitableBool.h>
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

    worker.Submit( MakeTask( "Flag1", [&]
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
            worker.Submit( MakeTask( "Counter", [&]
            {
                ++ counter;
            }));
        }

        ready = false;
        worker.Submit( MakeTask( "End", [&] { ready = true; } ));
    
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

        auto slowTask = MakeTask( "Slow", [&] { slowReady = true; } );
        slowTask.DelayFor( Ticks( 100 ));

        auto fastTask = MakeTask( "Fast", [&] { fastReady = true; } );

        TickWatch watch;

        worker.Submit( slowTask );
        worker.Submit( fastTask );

        fastReady.Wait();

        CHECK( false == slowReady );

        slowReady.Wait();

        CHECK_CLOSE( Ticks( 110 ), watch.Slice(), Ticks( 10 ));
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

        CHECK( ilist.size() == answer.size() );
        CHECK( true == std::equal( ilist.begin(), ilist.end(), answer.begin() ));
    }

    worker.Stop();
}


TEST( WorkerThreadThenTest )
{
    WorkerThread worker( "Then" );

    /// No result continuation ///
    {
        std::vector< Int > order;

        Task< void > t1 = MakeTask( "Then1",
        [&]
        {
            order.push_back( 1 );
        });

        Task< void > t2 = t1.Then( "Then2",
        [&] ( Task< void > )
        {
            order.push_back( 2 );
        });

        worker.Submit( t1 );

        t2.Wait();
        CHECK( 1 == order[0] && 2 == order[1] );
    }

    /// Continuation with Result ///
    {
        std::string name;

        Task< std::string > t1 = MakeTask( "Then1",
        [&]
        {
            return std::string( "Alice" );
        });

        Task< void > t2 = t1.Then( "Then2",
        [&] ( Task< std::string > t )
        {
            name = t.GetResult();
        });

        worker.Submit( t1 );

        t2.Wait();
        CHECK( "Alice" == name );
    }

    worker.Stop();
}


} // SUITE WorkerThreadSuite

} // namespace Caramel
