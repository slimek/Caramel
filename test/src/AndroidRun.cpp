// Caramel C++ Library Test - Android Entry

#include "CaramelTestPch.h"

#include <Caramel/Android/LogTraceAdapter.h>
#include <Caramel/Android/Streambuf.h>
#include <Caramel/Thread/Thread.h>
#include <UnitTest++/TestReporterCout.h>
#include <jni.h>
#include <iostream>


namespace Caramel
{

class RunTest
{
public:
	void Start();

private:
	void Main();

	Thread m_thread;
};


void RunTest::Start()
{
	m_thread.Start( "RunTest::Main", [=] { this->Main(); } );
}


void RunTest::Main()
{
	auto logTracer = new Android::LogTraceAdapter( "CaramelTest" );
	logTracer->BindBuiltinChannels( Trace::LEVEL_DEBUG );
	Trace::Listeners::AddManaged( logTracer );

	SetAlertHandler( ThrowAlertHandler );

	std::cout.rdbuf( new Android::Streambuf( "std::cout" ));

	std::cout << "Android::Streambuf created" << std::endl;

	CARAMEL_TRACE_INFO( "Caramel Test Starts" );

	/// Run All Tests ///

	using namespace UnitTest;

	TestReporterCout reporter;
	TestRunner runner( reporter );
	runner.RunTestsIf( Test::GetTestList(), NULL, True(), 0 );
}


} // namespace Caramel


extern "C"
{

jint JNI_OnLoad( JavaVM* vm, void* reserved )
{
    return JNI_VERSION_1_4;
}


void Java_com_slimek_carameltest_CaramelTestActivity_Run( JNIEnv* env, jobject thiz )
{
	auto testTop = new Caramel::RunTest;  // Do not delete it.
	testTop->Start();
}

} // extern "C"
