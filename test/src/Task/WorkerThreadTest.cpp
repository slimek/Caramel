// Caramel C++ Library Test - Task - Worker Thread Test

#include "CaramelTestPch.h"

#include <Caramel/Async/WaitableBool.h>
#include <Caramel/Task/WorkerThread.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( WorkerThreadSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Worker Thread Test
//

TEST( WorkerThreadTrivialTest )
{
    WorkerThread worker( "Trivial" );
    worker.Stop();
}


TEST( WorkerThreadNormalTest )
{
    WorkerThread worker( "Normal" );

    Bool flag1 = false;
    WaitableBool ready( false );

    worker.Submit( Task( "Flag1", [&]
    {
        flag1 = true;
        ready = true;
    }));

    ready.Wait();

    CHECK( true == flag1 );

    worker.Stop();
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE WorkerThreadSuite

} // namespace Caramel
