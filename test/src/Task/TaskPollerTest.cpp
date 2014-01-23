// Caramel C++ Library Test - Task - Task Poller Test

#include "CaramelTestPch.h"

#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Task/Strand.h>
#include <Caramel/Task/TaskPoller.h>
#include <Caramel/Thread/ThisThread.h>
#include <UnitTest++/UnitTest++.h>
#include <vector>


namespace Caramel
{

SUITE( TaskPollerSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Poller Test
//

TEST( TaskPollerNormalTest )
{
    TaskPoller poller;


    /// Execute One Task ///

    Bool done1 = false;

    poller.Submit( Task( "Normal1", [&] { done1 = true; } ));
    poller.PollOne();

    CHECK( true == done1 );


    /// Execute Many Tasks - Repeat 100 times ///

    for ( Uint rp = 0; rp < 100; ++ rp )
    {
        Int counter = 0;

        for ( Uint i = 0; i < 100; ++ i )
        {
            poller.Submit( Task( "Counter", [&] { ++ counter; } ));
        }

        poller.PollFor( Ticks( 50 ));

        CHECK( 100 == counter );
    }
}


TEST( TaskPollerDelayTest )
{
    TaskPoller poller;

    /// One Delay Tasks ///

    {
        Bool slowDone = false;
        Bool fastDone = false;
        
        Task slowTask( "Slow", [&] { slowDone = true; } );
        slowTask.DelayFor( Ticks( 100 ));

        Task fastTask( "Fast", [&] { fastDone = true; } );

        poller.Submit( slowTask );
        poller.Submit( fastTask );
        poller.PollOne();

        CHECK( true  == fastDone );
        CHECK( false == slowDone );

        ThisThread::SleepFor( Ticks( 100 ));

        poller.PollOne();

        CHECK( true == slowDone );
    }
}


TEST( TaskPollerStrandTest )
{
    TaskPoller poller;
    Strand strand;

    std::vector< Bool > dones( 3 );

    Task t0( "Work0", [&] { dones[0] = true; } );
    t0.Schedule( strand );

    Task t1( "Work1", [&] { dones[1] = true; } );
    t1.Schedule( strand );

    Task t2( "Work2", [&] { dones[2] = true; } );
    t2.Schedule( strand );

    poller.Submit( t0 );
    poller.Submit( t1 );
    poller.Submit( t2 );

    poller.PollOne();

    strand.CancelAll();

    poller.PollOne();

    CHECK( true  == dones[0] );
    //CHECK( false == dones[1] );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE TaskPollerSuite

} // namespace Caramel
