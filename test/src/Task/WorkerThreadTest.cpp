// Caramel C++ Library Test - Task - Worker Thread Test

#include "CaramelTestPch.h"

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

TEST( WorkerThreadTest )
{
    WorkerThread worker( "Test" );
}


///////////////////////////////////////////////////////////////////////////////

} // SUITE WorkerThreadSuite

} // namespace Caramel
