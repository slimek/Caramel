// Caramel C++ Library Test - Task - Task Poller Test

#include "CaramelTestPch.h"

#include <Caramel/Task/Strand.h>
#include <Caramel/Task/TaskPoller.h>
#include <Caramel/Thread/ThisThread.h>
#include <UnitTest++/UnitTest++.h>
#include <vector>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Poller Test
//

SUITE( TaskPollerSuite )
{

TEST( TaskPollerDelayTest )
{
    TaskPoller poller;

    Bool work1Done = false;
    Bool work2Done = false;

    Task t1( "Work1", [&] { work1Done = true; } );

    poller.Submit( t1 );
    poller.PollOne();

    CHECK( true == work1Done );

    Task t2( "Work2", [&] { work2Done = true; } );
    t2.DelayFor( Ticks( 500 ));

    poller.Submit( t2 );
    poller.PollOne();

    CHECK( false == work2Done );

    ThisThread::SleepFor( Ticks( 500 ));

    poller.PollOne();

    CHECK( true == work2Done );
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
    CHECK( false == dones[1] );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE TaskPollerSuite

} // namespace Caramel
