
#include <Caramel/Android/JniClass.h>
#include <Caramel/Android/LogTraceAdapter.h>
#include <Caramel/Error/Alert.h>
#include <Caramel/Object/Singleton.h>
#include <Caramel/Task/WorkerThread.h>
#include <Caramel/Trace/Trace.h>
#include <jni.h>


using namespace Caramel;
using namespace Caramel::Android;

static JniClass s_activityClass( "com/slimek/caramel/samples/jnihelpers/JniHelpersActivity" );
static JniClass s_testerClass( "com/slimek/caramel/samples/jnihelpers/Tester" );
static JniClass s_textView( "android/widget/TextView" );

static WorkerThread s_worker( "GlobalWorker" );

void Run()
{
	TraceInfo( "Native Run" );

	s_worker.Submit( "Run",
	[]
	{
		s_activityClass.Method< void >( "Salute" ).Call( "Hello world" );

		JniObject activity = s_activityClass.Method< JniObject >( "Instance" ).Call();

		JniObject tester = s_testerClass.NewObject();

		TraceInfo( "Tester.number: {0}", tester.GetInt( "number" ));
		TraceInfo( "Tester.name: {0}", tester.GetString( "name" ));

		tester.Method< void >( "ChangeNumber" ).Call( 456 );

		TraceInfo( "Tester.number: {0}", tester.GetInt( "number" ));

		TraceInfo( tester.Method< std::string >( "GetText" ).Call() );
	});
}


///////////////////////////////////////////////////////////////////////////////
//
// JNI Functions
//

extern "C"
{

jint JNI_OnLoad( JavaVM* vm, void* reserved )
{
	JniInitialize( vm, "com/slimek/caramel/samples/jnihelpers/JniHelpersActivity" );

	auto logTracer = new Android::LogTraceAdapter( "CaramelTest" );
	logTracer->BindBuiltinChannels( Trace::LEVEL_DEBUG );
	Trace::Listeners::AddManaged( logTracer );

	SetAlertHandler( ThrowAlertHandler );

	return JNI_VERSION_1_4;
}


void Java_com_slimek_caramel_samples_jnihelpers_JniHelpersActivity_Run(
	JNIEnv* evn, jobject thiz )
{
	Run();
}


} // extern "C"


///////////////////////////////////////////////////////////////////////////////
