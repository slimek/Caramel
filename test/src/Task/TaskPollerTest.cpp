// Caramel C++ Library Test - Task - Task Poller Test

#include "CaramelTestPch.h"

#include <Caramel/Task/TaskPoller.h>
#include <Caramel/Thread/ThisThread.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Poller Test
//

SUITE( TaskPollerSuite )
{

class TaskPollerTest : public UnitTest::Test
{
public:
    TaskPollerTest();

private:
    void RunImpl() const override;

    void DoRun();

    /// Task Functions ///

    Bool m_work1Done;
    Bool m_work2Done;



} TaskPollerTestInstance;


UnitTest::ListAdder adderTaskPollerTest( UnitTest::Test::GetTestList(), &TaskPollerTestInstance );


TaskPollerTest::TaskPollerTest()
    : UnitTest::Test( "TaskPollerTest", UnitTestSuite::GetSuiteName(), __FILE__, __LINE__ )
    , m_work1Done( false )
{
}


void TaskPollerTest::RunImpl() const
{
    const_cast< TaskPollerTest* >( this )->DoRun();
}


void TaskPollerTest::DoRun()
{
    TaskPoller poller;

    Task t1( "Work1", [=] { m_work1Done = true; } );

    poller.Submit( t1 );
    poller.PollOne();

    CHECK( true == m_work1Done );

    Task t2( "Work2", [=] { m_work2Done = true; } );
    t2.DelayFor( Ticks( 500 ));

    poller.Submit( t2 );
    poller.PollOne();

    CHECK( false == m_work2Done );

    ThisThread::SleepFor( Ticks( 550 ));

    poller.PollOne();

    CHECK( true == m_work2Done );



}


}

///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
