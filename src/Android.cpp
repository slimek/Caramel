// Caramel C++ Library - Android Facility - Implementation

#include "CaramelPch.h"

#include "Android/JniCenter.h"
#include <Caramel/Android/JniClass.h>
#include <Caramel/Android/LogTraceAdapter.h>
#include <Caramel/Android/Streambuf.h>
#include <Caramel/Thread/ThisThread.h>
#include <android/log.h>
#include <cstring>


namespace Caramel
{

namespace Android
{

//
// Contents
//
//   LogTraceAdapter
//   Streambuf
//   JniCenter
//   JniClass
//   JniObject
//   Detail::JniStaticMethodCore
//   Detail::JniMethodCore
//   Detail::JniTypeTraits
//   Detail::JniStringLocal
//   Detail::JniStringArrayLocal
//   Detail::JniObjectLocal
//   Detail::JniObjectArrayLocal
//   Detail::JniClass
//

///////////////////////////////////////////////////////////////////////////////
//
// Log Trace Adapter
//

LogTraceAdapter::LogTraceAdapter( const std::string& tagName )
    : m_tagName( tagName )
{
}


void LogTraceAdapter::Write( Trace::Level level, const std::string& message )
{
    CARAMEL_ASSERT( Trace::ExistsBuiltinChannel( level ));

    const auto priority = static_cast< android_LogPriority >( static_cast< Int >( level ) + 1 );

    __android_log_write( priority, m_tagName.c_str(), message.c_str() );
}


///////////////////////////////////////////////////////////////////////////////
//
// Streambuf
//

Streambuf::Streambuf( std::string name )
    : m_name( std::move( name ))
{
	this->setp( &m_buffer[0], &m_buffer[ BUFFER_SIZE - 1 ] );
}


Int Streambuf::overflow( Int c )
{
	if ( c == traits_type::eof() )
	{
		*this->pptr() = traits_type::to_char_type( c );
		this->sbumpc();
	}

	return this->sync() ? traits_type::eof() : traits_type::not_eof( c );
}


Int Streambuf::sync()
{
	Int rc = 0;
	if ( this->pbase() != this->pptr() )
	{
		Char writebuf[ BUFFER_SIZE + 1 ];
		std::memcpy( writebuf, this->pbase(), this->pptr() - this->pbase() );
		writebuf[ this->pptr() - this->pbase() ] = '\0';

		rc = __android_log_write( ANDROID_LOG_INFO, m_name.c_str(), writebuf ) > 0;
		this->setp( &m_buffer[0], &m_buffer[ BUFFER_SIZE - 1 ] );
	}

	return rc;
}


///////////////////////////////////////////////////////////////////////////////
//
// JNI Center
//

JniCenter::~JniCenter()
{
	if ( m_classLoader )
	{
		this->GetEnvOfCurrentThread()->DeleteGlobalRef( m_classLoader );
	}
}


void JniCenter::Initialize( JavaVM* jvm, const std::string& userClassPath )
{
	CARAMEL_ASSERT( jvm );
	CARAMEL_ASSERT( ! m_jvm );

	m_jvm = jvm;

	JNIEnv* env = this->GetEnvOfCurrentThread();

	// Get a user-defined class.
	auto userClass = env->FindClass( userClassPath.c_str() );

	auto classClass = env->FindClass( "java/lang/Class" );
	auto classLoaderClass = env->FindClass( "java/lang/ClassLoader" );

	auto getClassLoaderMethod = env->GetMethodID(
		classClass, "getClassLoader", "()Ljava/lang/ClassLoader;" );

	m_classLoader = env->NewGlobalRef(
		env->CallObjectMethod( userClass, getClassLoaderMethod ));
	m_findClassMethod = env->GetMethodID(
		classLoaderClass, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;" );

	CARAMEL_ASSERT( m_findClassMethod );
}


// The JNIEnv of each thread.
static thread_local JNIEnv* tls_threadJniEnv = nullptr;

JNIEnv* JniCenter::GetEnvOfCurrentThread()
{
	if ( nullptr != tls_threadJniEnv ) { return tls_threadJniEnv; }

	CARAMEL_ASSERT( m_jvm );


	if ( JNI_OK == m_jvm->GetEnv( (void**)&tls_threadJniEnv, JNI_VERSION_1_4 ))
	{
		CARAMEL_ASSERT( tls_threadJniEnv );

		// This thread is already attached to Java VM at somewhere.

		TraceDebug( "JniCenter: This thread already has its own Env" );
		return tls_threadJniEnv;
	}

	if ( 0 == m_jvm->AttachCurrentThread( &tls_threadJniEnv, nullptr ))
	{
		CARAMEL_ASSERT( tls_threadJniEnv );

		// This thread has been attached to Java VM.
		// Set an exit routine to detach if from Java VM when it exits.

		JavaVM* jvm = m_jvm;
		ThisThread::AtThreadExit( [jvm] { jvm->DetachCurrentThread(); } );

		return tls_threadJniEnv;
	}

	CARAMEL_ALERT( "Failed to get JNIEvn for current thread" );
}


jclass JniCenter::GetClassId( const std::string& classPath )
{
	auto env = this->GetEnvOfCurrentThread();

	Detail::JniStringLocal jname( classPath, env );

	jclass klass = static_cast< jclass >(
		env->CallObjectMethod( m_classLoader, m_findClassMethod, jname.Jni() ));

	if ( ! klass )
	{
		CARAMEL_ALERT( "GetClassId() failed, classPath: \"{0}\"", classPath );
	}

	return klass;
}


//
// Stand-alone Functions
//

void JniInitialize( JavaVM* jvm, const std::string& userClassPath )
{
	JniCenter::Instance()->Initialize( jvm, userClassPath );
}


///////////////////////////////////////////////////////////////////////////////
//
// JNI Class
//

JniClass::JniClass( std::string classPath )
	: m_classPath( std::move( classPath ))
{}


///////////////////////////////////////////////////////////////////////////////
//
// JNI Object
// - Keep reference counting of JniObjectLocal and JniClassLocal
//

JniObject::JniObject( jobject obj, JNIEnv* env )
	: m_object( std::make_shared< Detail::JniObjectLocal >( obj, env ))
	, m_class( std::make_shared< Detail::JniClassLocal >( obj, env ))
	, m_env( env )
{}


template< typename T >
jfieldID JniObject::GetFieldId( const std::string& fieldName ) const
{
	return m_env->GetFieldID(
		m_class->Jni(), fieldName.c_str(), Detail::JniTypeTraits< T >::Signature().c_str() );
}


Bool JniObject::GetBool( const std::string& fieldName ) const
{
	jfieldID fid = this->GetFieldId< Bool >( fieldName );

	return m_env->GetBooleanField( m_object->Jni(), fid );
}


Int JniObject::GetInt( const std::string& fieldName ) const
{
	jfieldID fid = this->GetFieldId< Int >( fieldName );

	return m_env->GetIntField( m_object->Jni(), fid );
}


Int64 JniObject::GetLong( const std::string& fieldName ) const
{
	jfieldID fid = this->GetFieldId< Int64 >( fieldName );

	return m_env->GetLongField( m_object->Jni(), fid );
}


std::string JniObject::GetString( const std::string& fieldName ) const
{
	jfieldID fid = this->GetFieldId< std::string >( fieldName );

    return Detail::JniStringLocal(
		(jstring)m_env->GetObjectField( m_object->Jni(), fid ), m_env ).ToString();
}


///////////////////////////////////////////////////////////////////////////////
//
// JNI Static Method Core
//

namespace Detail
{

JniStaticMethodCore::JniStaticMethodCore( std::string&& classPath, std::string&& methodName )
	: m_classPath( std::move( classPath ))
	, m_methodName( std::move( methodName ))
{}


void JniStaticMethodCore::BuildMethod( const std::string& signature )
{
	auto center = JniCenter::Instance();

	m_env = center->GetEnvOfCurrentThread();
	m_class = center->GetClassId( m_classPath );
	m_method = m_env->GetStaticMethodID( m_class, m_methodName.c_str(), signature.c_str() );

	if ( ! m_method )
	{
		CARAMEL_THROW(
			"GetStaticMethodID() failed, classPath: \"{0}\", methodName: \"{1}\", signature: \"{2}\"",
			m_classPath, m_methodName, signature );
	}
}


} // namespace Detail


///////////////////////////////////////////////////////////////////////////////
//
// JNI Type Traits
//

namespace Detail
{

//
// Signatures
//

std::string JniTypeTraits< void >::Signature()							{ return "V"; }
std::string JniTypeTraits< Bool >::Signature() 							{ return "Z"; }
std::string JniTypeTraits< Int >::Signature()							{ return "I"; }
std::string JniTypeTraits< Int64 >::Signature()                         { return "J"; }
std::string JniTypeTraits< Float >::Signature()							{ return "D"; }
std::string JniTypeTraits< std::string >::Signature() 					{ return "Ljava/lang/String;"; }
std::string JniTypeTraits< std::vector< std::string > >::Signature() 	{ return "[Ljava/lang/String;"; }
std::string JniTypeTraits< JniObject >::Signature() 					{ return "Ljava/lang/Object;"; }
std::string JniTypeTraits< std::vector< JniObject > >::Signature()		{ return "[Ljava/lang/Object;"; }


} // namespace Detail


///////////////////////////////////////////////////////////////////////////////
//
// JNI Local Wrappers
//

namespace Detail
{

//
// JNI Local for String
//

JniStringLocal::JniStringLocal( const std::string& cs, JNIEnv* env )
	: m_jstring( env->NewStringUTF( cs.c_str() ))
	, m_env( env )
{}


JniStringLocal::JniStringLocal( jstring js, JNIEnv* env )
	: m_jstring( js )
	, m_env( env )
{}


JniStringLocal::~JniStringLocal()
{
	if ( m_jstring )
	{
		m_env->DeleteLocalRef( m_jstring );
	}
}


std::string JniStringLocal::ToString() const
{
	const Char* chars = m_env->GetStringUTFChars( m_jstring, nullptr );

	if ( ! chars ) { return std::string(); }

	const std::string str( chars );
	m_env->ReleaseStringUTFChars( m_jstring, chars );

	return str;
}


//
// JNI Local for String Array
//

JniStringArrayLocal::JniStringArrayLocal( const std::vector< std::string >& csa, JNIEnv* env )
	: m_env( env )
{
	jclass stringClass = env->FindClass( "java/lang/String" );
	m_jobjectArray = env->NewObjectArray( csa.size(), stringClass, nullptr );

	for ( uint i = 0; i < csa.size(); ++ i )
	{
		jstring s = env->NewStringUTF( csa[i].c_str() );
		env->SetObjectArrayElement( m_jobjectArray, i, s );
		env->DeleteLocalRef( s );
	}

	env->DeleteLocalRef( stringClass );
}


JniStringArrayLocal::~JniStringArrayLocal()
{
	m_env->DeleteLocalRef( m_jobjectArray );
}


//
// JNI Local for Object
//

JniObjectLocal::JniObjectLocal( jobject obj, JNIEnv* env )
	: m_jobject( obj )
	, m_env( env )
{}


JniObjectLocal::~JniObjectLocal()
{
	m_env->DeleteLocalRef( m_jobject );
}


JniObjectLocal::operator JniObject() const
{
	return JniObject( m_env->NewLocalRef( m_jobject ), m_env );
}


//
// JNI Local for Object Array
//

JniObjectArrayLocal::JniObjectArrayLocal( jobjectArray objs, JNIEnv* env )
	: m_jobjectArray( objs )
	, m_env( env )
{
}


JniObjectArrayLocal::~JniObjectArrayLocal()
{
	m_env->DeleteLocalRef( m_jobjectArray );
}


JniObjectArrayLocal::operator std::vector< JniObject >() const
{
	const int length = m_env->GetArrayLength( m_jobjectArray );

	std::vector< JniObject > objects;
	objects.reserve( length );

	for ( int i = 0; i < length; ++ i )
	{
		jobject elem = m_env->GetObjectArrayElement( m_jobjectArray, i );
		objects.push_back( JniObject( elem, m_env ));
	}

	return objects;
}


//
// JNI Local for Class
//

JniClassLocal::JniClassLocal( jobject obj, JNIEnv* env )
	: m_jclass( env->GetObjectClass( obj ))
	, m_env( env )
{
}


JniClassLocal::~JniClassLocal()
{
	m_env->DeleteLocalRef( m_jclass );
}


} // namespace Detail


///////////////////////////////////////////////////////////////////////////////
//
// Validation
//

#define STATIC_ASSERT_LOG_TRACE_LEVEL( name ) \
    static_assert( ANDROID_LOG_ ## name == static_cast< Int >( Trace::LEVEL_ ## name + 1 ), "Log level " # name )

STATIC_ASSERT_LOG_TRACE_LEVEL( DEBUG );
STATIC_ASSERT_LOG_TRACE_LEVEL( INFO );
STATIC_ASSERT_LOG_TRACE_LEVEL( WARN );
STATIC_ASSERT_LOG_TRACE_LEVEL( ERROR );


///////////////////////////////////////////////////////////////////////////////

} // namespace Android

} // namespace Caramel
