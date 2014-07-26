// Caramel C++ Library Test - Thread - Spin Mutex Suite

#include "CaramelTestPch.h"

#include <Caramel/Thread/SpinMutex.h>
#include <Caramel/Thread/Thread.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( SpinMutexSuite )
{

SpinMutex s_mutex;
Int s_value = 0;
Int s_count = 0;

const Uint LOOP = 100000;

void Execute()
{
    for ( Uint i = 0; i < LOOP; ++ i )
    {
        SpinMutex::ScopedLock lock( s_mutex );
        ++ s_value;
        CHECK( 1 == s_value );
        ++ s_count;
        -- s_value;
    }
}


TEST( SpinMutexTest )
{
    /// Recover Test ///

    {
        SpinMutex::ScopedLock lock( s_mutex );
    }

    {
        SpinMutex::ScopedLock lock( s_mutex );
    }


    /// Race Test ///

    Thread t1( "SpinMutexExec1", [=] { Execute(); } );
    Thread t2( "SpinMutexExec2", [=] { Execute(); } );
    Thread t3( "SpinMutexExec3", [=] { Execute(); } );

    t1.Join();
    t2.Join();
    t3.Join();

    CHECK( s_count == LOOP * 3 );
}


} // SUITE SpinMutexSuite

} // namespace Caramel
