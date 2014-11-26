
#include <Caramel/Android/JniClass.h>


using namespace Caramel;
using namespace Caramel::Android;

static JniClass s_activity( "com/slimek/caramel/samples/jnihelpers/JniHelpersActivity" );


void OnClick()
{
	auto method = s_activity.Method< void >( "UpdateLabel" );
	method.Call();
	method.Call( "Hello world", 42 );
}
