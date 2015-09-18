// Caramel C++ Library Test - Thread - Mutex Locks Suite

#include "CaramelTestPch.h"

#include <Caramel/Task/AsyncSubmit.h>
#include <Caramel/Thread/MutexLocks.h>
#include <Caramel/Thread/Thread.h>
#include <Caramel/Thread/ThisThread.h>
#include <Caramel/Thread/WaitableBool.h>
#include <condition_variable>


namespace Caramel
{

SUITE( MutexLocks )
{

static std::mutex s_mutex;
static Int s_value = 0;
static Int s_count = 0;

static const Uint LOOP = 100000;

static void Execute()
{
    for ( Uint i = 0; i < LOOP; ++ i )
    {
        LockGuard lock( s_mutex );
        ++ s_value;
        CHECK( 1 == s_value );
        ++ s_count;
        -- s_value;
    }
}


TEST( LockGuard )
{
    /// Recover Test ///

    {
        LockGuard lock( s_mutex );
    }

    {
        LockGuard lock( s_mutex );
    }


    /// Race Test ///

    Thread t1( "LockExec1", [=] { Execute(); } );
    Thread t2( "LockExec2", [=] { Execute(); } );
    Thread t3( "LockExec3", [=] { Execute(); } );

    t1.Join();
    t2.Join();
    t3.Join();

    CHECK( s_count == LOOP * 3 );
}


TEST( UniqueLock )
{
    /// Recover Test ///

    {
        UniqueLock lock( s_mutex );
    }

    {
        UniqueLock lock( s_mutex );
    }


    /// Cooperate with std::condition_variable
    
    s_value = 0;
    std::condition_variable cond;
    auto pcond = &cond;

    auto task = AsyncSubmit( [=]
    {
        UniqueLock lock( s_mutex );
        while ( s_value < 2 )
        {
            pcond->wait( lock );
        }
    });

    {
        UniqueLock lock( s_mutex );
        s_value = 1;
    }
    cond.notify_one();

    CHECK( ! task.IsDone() );

    {
        UniqueLock lock( s_mutex );
        s_value = 2;
    }
    cond.notify_one();

    task.Wait();
}


} // SUITE MutexLocks

} // namespace Caramel
