// Caramel C++ Library Test - Android Entry

#include "CaramelTestPch.h"

#include "Utils/AssetPath.h"
#include <Caramel/Android/LogTraceAdapter.h>
#include <Caramel/Android/Streambuf.h>
#include <Caramel/Functional/ScopeExit.h>
#include <UnitTest++/TestReporterCout.h>
#include <jni.h>
#include <android/asset_manager.h>
#include <iostream>
#include <thread>


namespace Caramel
{

class RunTest
{
public:
	RunTest();
	void Start();

private:
	void Main();
};


RunTest::RunTest()
{
	auto logTracer = new Android::LogTraceAdapter( "CaramelTest" );
	logTracer->BindBuiltinChannels( Trace::LEVEL_DEBUG );
	Trace::Listeners::AddManaged( logTracer );

	SetAlertHandler( ThrowAlertHandler );
}


void RunTest::Start()
{
	std::thread( [=] { this->Main(); } ).detach();
}


void RunTest::Main()
{
	auto strbuf = std::make_shared< Android::Streambuf >( "std::cout" );

	auto backup = std::cout.rdbuf();
	auto scope = ScopeExit( [=] { std::cout.rdbuf( backup ); });

	std::cout.rdbuf( strbuf.get() );

	std::cout << "Android::Streambuf created" << std::endl;

	CARAMEL_TRACE_INFO( "Caramel Test Starts" );


	using namespace UnitTest;

	TestReporterCout reporter;
	TestRunner runner( reporter );

	//#define RUN_SUITE

	#if defined( RUN_SUITE )
	{
		runner.RunTestsIf( Test::GetTestList(), RUN_SUITE, True(), 0 );
	}
	#else
	{
		/// Run All Tests ///
		runner.RunTestsIf( Test::GetTestList(), NULL, True(), 0 );
	}
	#endif
}


} // namespace Caramel


///////////////////////////////////////////////////////////////////////////////
//
// JNI Functions
//

extern "C"
{

jint JNI_OnLoad( JavaVM* vm, void* reserved )
{
    return JNI_VERSION_1_4;
}


static AAssetManager* s_assetManager = nullptr;

void Java_com_slimek_carameltest_CaramelTestActivity_Run(
	JNIEnv* env, jobject thiz, jobject assetManager )
{
	s_assetManager = AAssetManager_fromJava( env, assetManager );

	static auto testTop = new Caramel::RunTest;  // Do not delete it.
	testTop->Start();
}

} // extern "C"
