// Caramel C++ Library Test - Task - Task Timer Suite

#include "CaramelTestPch.h"

#include <Caramel/Task/TaskTimer.h>
#include <Caramel/Task/TaskPoller.h>
#include <Caramel/Task/WorkerThread.h>
#include <Caramel/Thread/ThisThread.h>
#include <atomic>


namespace Caramel
{

SUITE( TaskTimer )
{

TEST( TaskTimerTrivial )
{
    TaskTimer timer;  // not-a-timer
}


TEST( TaskTimerPoller )
{
    TaskPoller poller;
    std::atomic< Int > counter{ 0 };
    
    TaskTimer timer( "Timer", poller, Ticks( 100 ),
    [&]
    {
        ++ counter;
    });

    poller.PollOne();

    CHECK( 0 == counter.load() );

    ThisThread::SleepFor( Ticks( 200 ));  // 200 ms
    poller.PollOne();

    CHECK( 1 == counter.load() );

    poller.PollOne();

    CHECK( 1 == counter.load() );

    ThisThread::SleepFor( Ticks( 300 ));  // 500 ms
    poller.PollFor( Ticks( 10 ));

    CHECK( 2 == counter.load() );

    // NOTES: TaskTimer submit the next task after the current completed.
    //        Even the time passed 300 ms, before the poller execute the task,
    //        it can't submit more task.
}


TEST( TaskTimerWorker )
{
    WorkerThread worker( "TaskTimerWorker" );
    std::atomic< Int > counter{ 0 };

    TaskTimer timer( "Timer", worker, Ticks( 100 ),
    [&]
    {
        ++ counter;
    });

    CHECK( 0 == counter.load() );

    ThisThread::SleepFor( Ticks( 150 ));  // 150 ms

    CHECK( 1 == counter.load() );

    ThisThread::SleepFor( Ticks( 200 ));  // 350 ms

    CHECK( 3 == counter.load() );

    worker.Stop();
}


//
// It should be safe the cancel the timer in its work.
//
TEST( TaskTimerCancel )
{
    WorkerThread worker( "TaskTimerWorker-Cancel" );
    std::atomic< Int > counter{ 0 };

    TaskTimer timer;
    timer.Start( "TaskTimerCancel", worker, Ticks( 10 ),
    [&]
    {
        const Int value = ++ counter;
        if ( value == 10 )
        {
            timer.Cancel();
        }
    });

    ThisThread::SleepFor( Ticks( 200 ));

    CHECK( 10 == counter.load() );

    worker.Stop();
}


} // SUITE TaskTimer

} // namespace Caramel
