// Caramel C++ Library - Android Facility - Detail - JNI Constructor Header

#ifndef __CARAMEL_ANDROID_DETAIL_JNI_CONSTRUCTOR_H
#define __CARAMEL_ANDROID_DETAIL_JNI_CONSTRUCTOR_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Android/Detail/JniMethod.h>
#include <Caramel/Android/JniObject.h>


namespace Caramel
{

namespace Android
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// JNI Constructor
// - Used for creating new JAVA object.
//

class JniConstructor
{
public:
	
	explicit JniConstructor( std::string classPath );
	
	// Call with no parameter
	JniObject Call();
	
	template< typename... Args >
	JniObject Call( const Args&... args );
	
private:

	void BuildMethod( const std::string& signature );

	template< typename... JniArgs >
	JniObject CallMethod( const JniArgs&... jniArgs );
	
	std::string m_classPath;
	
	JNIEnv* m_env { nullptr };
	jclass m_class { nullptr };
	jmethodID m_methodId { nullptr };
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline JniObject JniConstructor::Call()
{
	this->BuildMethod( MakeJniSignature< void >() );
	return this->CallMethod();
}


template< typename... Args >
inline JniObject JniConstructor::Call( const Args&... args )
{
	this->BuildMethod( MakeJniSignature< void >( args... ));
	return this->CallMethod(
		( typename JniTypeTraits< Args >::Local( args, m_env )).Jni()... );
}


template< typename... JniArgs >
inline JniObject JniConstructor::CallMethod( const JniArgs&... jniArgs )
{
	jobject jret = m_env->NewObject( m_class, m_methodId, jniArgs... );
	JniObjectLocal local( jret, m_env );
	return local;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Android

} // namespace Caramel

#endif // __CARAMEL_ANDROID_DETAIL_JNI_CONSTRUCTOR_H
