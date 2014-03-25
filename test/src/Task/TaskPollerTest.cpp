// Caramel C++ Library Test - Task - Task Poller Test

#include "CaramelTestPch.h"

#include <Caramel/Chrono/TickClock.h>
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

    poller.Submit( MakeTask( "Normal1", [&] { done1 = true; } ));
    poller.PollOne();

    CHECK( true == done1 );


    /// Execute Many Tasks - Repeat 100 times ///

    for ( Uint rp = 0; rp < 100; ++ rp )
    {
        Int counter = 0;

        for ( Uint i = 0; i < 100; ++ i )
        {
            poller.Submit( MakeTask( "Counter", [&] { ++ counter; } ));
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
        
        auto slowTask = MakeTask( "Slow", [&] { slowDone = true; } );
        slowTask.DelayFor( Ticks( 100 ));

        auto fastTask = MakeTask( "Fast", [&] { fastDone = true; } );

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


TEST( TaskPollerThenTest )
{
    TaskPoller poller;

    {
        Bool done1 = false;
        Bool done2 = false;

        auto task1 = MakeTask( "Task1", [&] { done1 = true; } );
        auto task2 = task1.Then( std::string( "Task2" ), [&] ( Task< void > ) { done2 = true; } );

        poller.Submit( task1 );
        poller.PollFor( Ticks( 100 ));

        CHECK( true == done1 && true == done2 );
    }

    /// Task Faulted ///
    {
        Bool done4 = false;

        auto task3 = MakeTask( "Task3", [] { CARAMEL_THROW( "Shock" ); } );
        
        auto task4 = task3.Then( "Task4",
        [&] ( Task< void > )
        {
            done4 = true;
        });

        poller.Submit( task3 );
        poller.PollFor( Ticks( 100 ));

        CHECK( true == done4 && true == task3.IsFaulted() );
    }

    /// Then with Void ///
    {
        Bool done5 = false;
        Bool done6 = false;

        auto task5 = MakeTask( "Task5", [&] { done5 = true; } );

        auto task6 = task5.Then( "Task6",
        [&] ()
        {
            done6 = true;
        });

        poller.Submit( task5 );
        poller.PollFor( Ticks( 100 ));

        CHECK( true == done5 && true == done6 );
    }

}


///////////////////////////////////////////////////////////////////////////////

} // SUITE TaskPollerSuite

} // namespace Caramel
