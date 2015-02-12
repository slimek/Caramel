// Caramel C++ Library Test - Task - Thread Pool Suite

#include "CaramelTestPch.h"

#include <Caramel/Task/ThreadPool.h>
#include <Caramel/Thread/ThisThread.h>
#include <atomic>
#include <vector>


namespace Caramel
{

SUITE( ThreadPoolSuite )
{

TEST( ThreadPoolTrivialTest )
{
    ThreadPool pool( "Trivial", 2 );
    pool.Shutdown();
}


TEST( ThreadPoolNormalTest )
{
    ThreadPool pool( "Normal", 4 );

    
    /// Execute 1 Task ///

    Bool flag1 = false;

    auto t1 = MakeTask( "Flag1", [&] { flag1 = true; } );
    pool.Submit( t1 );

    t1.Wait();

    CHECK( true == flag1 );


    TickWatch watch;

    /// Execute 4096 Tasks ///

    std::atomic< Int > count( 0 );

    const Uint N_TASKS = 4096;

    for ( Uint i = 0; i < N_TASKS; ++ i )
    {
        auto tn = MakeTask( "ManyTasks", [&] { ++ count; } );
        pool.Submit( tn );
    }

    while ( N_TASKS != count.load() )
    {
        ThisThread::SleepFor( Ticks( 10 ));
    }

    pool.Shutdown();
}


//
// Shutdown a ThreadPool while it has some tasks pending.
//
// EXPECTED: Discard all pending tasks and return as soon as possible.
//
TEST( ThreadPoolShutdownTest )
{
    ThreadPool pool( "Shutdown", 4 );

    for ( Uint i = 0; i < 256; ++ i )
    {
        pool.Submit( MakeTask( "Pending",
            [] { ThisThread::SleepFor( Ticks( 10 )); } ));
    }

    CHECK( pool.GetNumReadyTasks() > 0 );

    TickWatch watch;
    pool.Shutdown();

    CHECK( watch.Elapsed() < Ticks( 100 ));
}


} // SUITE ThreadPoolSuite

} // namespace Caramel
