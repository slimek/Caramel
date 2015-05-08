// Caramel C++ Library Test - Thread - Lock Guard Suite

#include "CaramelTestPch.h"

#include <Caramel/Thread/MutexLocks.h>
#include <Caramel/Thread/Thread.h>


namespace Caramel
{

SUITE( LockGuard )
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
    s_count = 0;

    /// Recover Test - the lock guard should automatically released ///

    {
        LockGuard lock( s_mutex );
    }

    {
        LockGuard lock( s_mutex );
    }


    /// Racing Test ///

    Thread t1( "LockGuardExec1", [=] { Execute(); });
    Thread t2( "LockGuardExec2", [=] { Execute(); });
    Thread t3( "LockGuardExec3", [=] { Execute(); });
     
    t1.Join();
    t2.Join();
    t3.Join();

    CHECK( LOOP * 3 == s_count );
    CHECK( 0 == s_value );
}


} // SUITE LockGuard

} // namespace Caramel
