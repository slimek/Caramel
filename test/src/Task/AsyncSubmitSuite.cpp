// Caramel C++ Library Test - Task - Async Submit Suite

#include "CaramelTestPch.h"

#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Task/AsyncSubmit.h>
#include <Caramel/Thread/ThisThread.h>
#include <future>


namespace Caramel
{

SUITE( AsyncSubmit )
{

TEST( AsyncSubmit )
{
    Task< Int > t1( [] { return 42; });

    AsyncSubmit( t1 );
    CHECK( 42 == t1.GetResult() );

    Task< std::string > t2( [] { return "Alice"; });
    
    // Pass a rvalue
    AsyncSubmit( Task< std::string >( t2 ));
    CHECK( "Alice" == t2.GetResult() );

    auto t3 = AsyncSubmit( [] { return 3.1416f; } );
    CHECK( 3.1416f == t3.GetResult() );

    Bool done4 = false;
    auto t4 = AsyncSubmit( "AsyncSubmit4", [&] { done4 = true; });

    t4.Wait();
    CHECK( true == done4 );


    // Make sure that an async thread is not the current thread

    auto t5 = AsyncSubmit( [] { return ThisThread::GetId(); });

    CHECK( ThisThread::GetId() != t5.GetResult() );
}


TEST( AsyncSubmitProxy )
{
    Task< void > t1( "Test1", [] {} );
    Task< Int >  t2( "Test2", [] { return 42; } );

    {
        AsyncSubmitProxy async;

        async.Submit( t1 );
        async.Submit( t2 );

        t1.Wait();
        t2.Wait();

        CHECK( 42 == t2.GetResult() );


        // Make sure that an async thread is not the current thread.

        auto t3 = async.Submit( "GetThreadId", [&] { return ThisThread::GetId(); });

        CHECK( ThisThread::GetId() != t3.GetResult() );
    }

    // Even the AsyncSubmitProxy object has been destroyed, you may still continuate these tasks.

    Bool done1 = false;
    auto then1 = t1.Then( [&] { done1 = true; });

    Int value2 = 0;
    auto then2 = t2.Then( [&] ( Int result ) { value2 = result * 2; });

    then1.Wait();
    then2.Wait();

    CHECK( true == done1 );
    CHECK( 84 == value2 );
}


} // SUITE AsyncSubmit

} // namespace Caramel
