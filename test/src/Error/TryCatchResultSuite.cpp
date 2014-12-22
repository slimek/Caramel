// Caramel C++ Library Test - Error - Try-Catch Result Suite

#include "CaramelTestPch.h"

#include <Caramel/Error/CatchException.h>
#include <Caramel/Task/Task.h>
#include <Caramel/Task/TaskPoller.h>


namespace Caramel
{

SUITE( TryCatchResultSuite )
{

void TestException( const TryCatchResult& result )
{
    CHECK( result.anyFailure == nullptr );
    CHECK( result.exception );
}

void TestAnyFailure( const TryCatchResult& result, Int code )
{
    auto failure = result.anyFailure;

    CHECK( failure );
    CHECK( failure->Code() == code );
    CHECK( result.exception );
}


TEST( TryCatchResultTest )
{
    auto xc1 = CatchException( [] { CARAMEL_THROW( "I'll be back!" ); } );
    TestException( xc1 );

    auto xc2 = CatchException( [] { throw AnyFailure( 42 ); } );
    TestAnyFailure( xc2, 42 );

    TaskPoller poller;

    auto task1 = MakeTask( "Task1", [] { CARAMEL_THROW( "Voy a revolver" ); } );
    poller.Submit( task1 );
    poller.PollOne();
    TestException( task1.Catch() );

    auto task2 = MakeTask( "Task2", [] { throw AnyFailure( 51 ); } );
    poller.Submit( task2 );
    poller.PollOne();
    TestAnyFailure( task2.Catch(), 51 );

    auto task3 = MakeTask( "Task3", [] {} );
    poller.Submit( task3 );
    poller.PollOne();

    auto res3 = task3.Catch();
    CHECK( res3.doneState == TASK_STATE_RAN_TO_COMP );
    CHECK( res3.anyFailure == nullptr );
    CHECK( res3.exception == nullptr );
}

} // SUITE TryCatchResultSuite

} // namespace Caramel
