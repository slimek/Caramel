// Caramel C++ Library Test - String - Sprintf Test

#include "CaramelTestPch.h"

#include <Caramel/String/Sprintf.h>
#include <Caramel/Thread/Thread.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

SUITE( SprintfSuite )
{

///////////////////////////////////////////////////////////////////////////////
//
// Sprintf Test
//

TEST( SprintfTest )
{
    // Fundamental Types

    CHECK_EQUAL( "i:42",   Sprintf( "i:%d", 42 ));
    CHECK_EQUAL( "i:-216", Sprintf( "i:%d", -216 ));
    CHECK_EQUAL( "u:75",   Sprintf( "u:%u", 75 ));
}


void Execute()
{
    for ( Uint i = 0; i < 10000; ++ i )
    {
        const std::string step1 = Sprintf( "Hello UnitTest! count: %d", i );
        Sprintf( "[%04d] : %s", step1 );
    }
}

TEST( ConcurrentSprintfTest )
{
    Thread t1( "Exec1", [=] { Execute(); } );
    Thread t2( "Exec2", [=] { Execute(); } );
    Thread t3( "Exec3", [=] { Execute(); } );

    t1.Join();
    t2.Join();
    t3.Join();
}

} // SUITE SprintfSuite

} // namespace Caramel
