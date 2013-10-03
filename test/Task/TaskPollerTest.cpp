// Caramel C++ Library Test - Task - Task Poller Test

#include "CaramelTestPch.h"

#include <Caramel/Task/TaskPoller.h>
#include <UnitTest++/UnitTest++.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Task Poller Test
//

class TaskPollerTest : public UnitTest::Test
{
public:
    TaskPollerTest();

private:
    void RunImpl() const override;

    void DoRun();

    /// Task Functions ///

    void Work1();

    Bool m_work1Done;



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

    Task t1( "Work1", [=] { this->Work1(); } );

    poller.Submit( t1 );
    poller.PollOne();

    CHECK( m_work1Done == true );
}


void TaskPollerTest::Work1()
{
    CHECK( m_work1Done == false );

    m_work1Done = true;
}


///////////////////////////////////////////////////////////////////////////////
} // namespace Caramel
