// Caramel C++ Library Test - Thread - Thread Test

#include "CaramelTestPch.h"

#include <Caramel/Thread/Thread.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Thread Test
//

void Execute1();
void Execute2();

SUITE( ThreadSuite )
{

TEST( ThreadTest )
{
    Thread t0;

    Thread t1( "Execute1", &Execute1 );
    t1.Join();

    Thread t2( "Execute2", &Execute2 );
    t2.Join();
}

}  // ThreadSuite

void Execute1()
{
}

void Execute2()
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
