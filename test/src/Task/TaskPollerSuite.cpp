// Caramel C++ Library Test - Task - Task Poller Suite

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


//
// Task Poller with a Custom Clock
// - A custom clock affects the delay behavior.
//

class CustomClock
{
public:

    static TickPoint Now() { return m_now; }

    static void Reset() { m_now = TickClock::Now(); }
    static void Advance( Ticks s ) { m_now += s; }

private:
    static TickPoint m_now;
};

TickPoint CustomClock::m_now;


TEST( TaskPollerWithCustomClockTest )
{
    TaskPoller poller( MakeClockProxy< CustomClock >() );

    Bool done = false;

    auto task = MakeTask( "Delay", [&] { done = true; } );
    task.DelayFor( Ticks( 50 ));
    poller.Submit( task );

    ThisThread::SleepFor( Ticks( 100 ));

    poller.PollOne();

    CHECK( false == done );  // Not executed yet.

    CustomClock::Advance( Ticks( 25 ));
    poller.PollOne();

    CHECK( false == done );

    CustomClock::Advance( Ticks( 35 ));  // The sum is 60
    poller.PollOne();

    CHECK( true == done );
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

        CHECK( true == task3.IsFaulted() );

        // No matter task3 succeeded or failed, always execute task4.
        CHECK( true == done4 );
        
        // Catch the exception to prevent it from outputting a tracing message in unit test.
        const auto result = task3.Catch();
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


} // SUITE TaskPollerSuite

} // namespace Caramel
