
#include <Caramel/Android/JniClass.h>
#include <Caramel/Android/LogTraceAdapter.h>
#include <Caramel/Error/Alert.h>
#include <Caramel/Trace/Trace.h>
#include <jni.h>


using namespace Caramel;
using namespace Caramel::Android;

static JniClass s_activityClass( "com/slimek/caramel/samples/jnihelpers/JniHelpersActivity" );
static JniClass s_textView( "android/widget/TextView" );


void Run()
{
	CARAMEL_TRACE_INFO( "Native Run" );

	s_activityClass.Method< void >( "Salute" ).Call( std::string( "Hello world" ));

	JniObject activity = s_activityClass.Method< JniObject >( "Instance" ).Call();
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
