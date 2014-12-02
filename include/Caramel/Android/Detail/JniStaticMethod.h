// Caramel C++ Library - Android Facility - Detail - JNI Static Method Header

#ifndef __CARAMEL_ANDROID_DETAIL_JNI_STATIC_METHOD_H
#define __CARAMEL_ANDROID_DETAIL_JNI_STATIC_METHOD_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Android/Detail/JniLocals.h>
#include <Caramel/Android/Detail/JniSignature.h>
#include <Caramel/Android/Detail/JniTypeTraits.h>
#include <Caramel/Android/JniObject.h>
#include <jni.h>


namespace Caramel
{

namespace Android
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// JNI Static Method Core
//

class JniStaticMethodCore
{
protected:

	JniStaticMethodCore( std::string&& classPath, std::string&& methodName );


protected:

	void BuildMethod( const std::string& signature );

	std::string m_classPath;
	std::string m_methodName;

	JNIEnv*   m_env { nullptr };
	jclass    m_class { nullptr };
	jmethodID m_method { nullptr };
};


///////////////////////////////////////////////////////////////////////////////
//
// JNI Static Method
//

template< typename Result >
class JniStaticMethod : public JniStaticMethodCore
{
public:

	JniStaticMethod( std::string classPath, std::string methodName );


	// Call with no parameter.
	Result Call();

	template< typename... Args >
	Result Call( const Args&... args );


private:

	template< typename... JniArgs >
	Result CallMethod( const JniArgs&... jniArgs );
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Result >
inline JniStaticMethod< Result >::JniStaticMethod( std::string classPath, std::string methodName )
	: JniStaticMethodCore( std::move( classPath ), std::move( methodName ))
{}


//
// Call Methods
//

template< typename Result >
inline Result JniStaticMethod< Result >::Call()
{
	this->BuildMethod( MakeJniSignature< Result >() );
	return this->CallMethod();
}


template< typename Result >
template< typename... Args >
inline Result JniStaticMethod< Result >::Call( const Args&... args )
{
	this->BuildMethod( MakeJniSignature< Result >( args... ));
	return this->CallMethod(
		( typename JniTypeTraits< Args >::Local( args, m_env )).Jni()... );
}


template<>
template< typename... JniArgs >
inline void JniStaticMethod< void >::CallMethod( const JniArgs&... jniArgs )
{
	m_env->CallStaticVoidMethod( m_class, m_method, jniArgs... );
}


template<>
template< typename... JniArgs >
inline std::string JniStaticMethod< std::string >::CallMethod( const JniArgs&... jniArgs )
{
	jstring jstr = (jstring)m_env->CallStaticObjectMethod( m_class, m_method, jniArgs... );
	JniStringLocal local( jstr, m_env );
	return local.ToString();
}


template<>
template< typename... JniArgs >
inline JniObject JniStaticMethod< JniObject >::CallMethod( const JniArgs&... jniArgs )
{
	jobject jobj = m_env->CallStaticObjectMethod( m_class, m_method, jniArgs... );
	return JniObject( jobj, m_env );
}

///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Android

} // namespace Caramel

#endif // __CARAMEL_ANDROID_DETAIL_JNI_STATIC_METHOD_H
