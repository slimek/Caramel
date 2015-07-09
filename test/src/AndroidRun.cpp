// Caramel C++ Library Test - Android Entry

#include "CaramelTestPch.h"

#include "Utils/AssetReader.h"
#include "Utils/WritablePath.h"
#include <Caramel/Android/JniClass.h>
#include <Caramel/Android/JniInitialize.h>
#include <Caramel/Android/LogTraceAdapter.h>
#include <Caramel/Android/Streambuf.h>
#include <Caramel/Functional/ScopeExit.h>
#include <Caramel/Thread/Thread.h>
#include <UnitTest++/TestReporterCout.h>
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <iostream>
#include <thread>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Android Run Test Wrapper
//

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
	std::thread( [=]
    {
		Thread t;
		t.Start( "RunStart", [=] { this->Main(); } );
		t.Join();

    }).detach();
}


void RunTest::Main()
{
	auto strbuf = std::make_shared< Android::Streambuf >( "std::cout" );

	auto backup = std::cout.rdbuf();
	auto scope = ScopeExit( [=] { std::cout.rdbuf( backup ); });

	std::cout.rdbuf( strbuf.get() );

	std::cout << "Android::Streambuf created" << std::endl;

	TraceInfo( "Caramel Test Starts" );


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

static const std::string s_activityClassPath( "com/slimek/carameltest/CaramelTestActivity" );

extern "C"
{

jint JNI_OnLoad( JavaVM* vm, void* reserved )
{
	Caramel::Android::JniInitialize( vm, s_activityClassPath );

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


///////////////////////////////////////////////////////////////////////////////
//
// Asset Reader
//

namespace Caramel
{

AssetReader::AssetReader( const std::string& fileName )
{
	AAsset* asset = AAssetManager_open(
		s_assetManager, fileName.c_str(), AASSET_MODE_UNKNOWN );

	off_t fileSize = AAsset_getLength( asset );
	m_buffer.resize( fileSize );

	AAsset_read( asset, &m_buffer[0], fileSize );
	AAsset_close( asset );

	m_stream.reset( new InputMemoryStream( &m_buffer[0], m_buffer.size() ));
	m_reader.reset( new TextStreamReader( *m_stream ));
}


Bool AssetReader::ReadLine( std::string& line )
{
	return m_reader->ReadLine( line );
}


///////////////////////////////////////////////////////////////////////////////
//
// Writable Path
//

static Android::JniClass s_activity( s_activityClassPath );

Path WritablePath()
{
	const std::string cacheDir = s_activity.Method< std::string >( "GetWritablePath" ).Call();

	return Path( cacheDir );
}


///////////////////////////////////////////////////////////////////////////////
//
// Utilities Functions
//

AAssetManager* GetAssetManager()
{
	return s_assetManager;
}


} // namespace Caramel


///////////////////////////////////////////////////////////////////////////////
