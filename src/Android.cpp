// Caramel C++ Library - Android Facility - Implementation

#include "CaramelPch.h"

#include "Android/JniCenter.h"
#include <Caramel/Android/JniClass.h>
#include <Caramel/Android/LogTraceAdapter.h>
#include <Caramel/Android/Streambuf.h>
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
//   Detail::JniStaticMethodCore
//   Detail::JniTypeTraits
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

	CARAMEL_NOT_IMPLEMENTED();
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
// JNI Static Method Core
//

namespace Detail
{

JniStaticMethodCore::JniStaticMethodCore( std::string&& classPath, std::string&& methodName )
	: m_classPath( std::move( classPath ))
	, m_methodName( std::move( methodName ))
{}

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
std::string JniTypeTraits< std::string >::Signature() 					{ return "Ljava/lang/String;"; }

/*
std::string JniTypeTraits< Float >::Signature()							{ return "D"; }
std::string JniTypeTraits< std::vector< std::string > >::Signature() 	{ return "[Ljava/lang/String;"; }
std::string JniTypeTraits< JniObject >::Signature() 					{ return "Ljava/lang/Object;"; }
std::string JniTypeTraits< std::vector< JniObject > >::Signature()		{ return "[Ljava/lang/Object;"; }
*/

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
