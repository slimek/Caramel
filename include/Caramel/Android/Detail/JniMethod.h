// Caramel C++ Library - Android Facility - Detail - JNI Method Header

#ifndef __CARAMEL_ANDROID_DETAIL_JNI_METHOD_H
#define __CARAMEL_ANDROID_DETAIL_JNI_METHOD_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Android/Detail/JniSignature.h>
#include <Caramel/Android/Detail/JniTypeTraits.h>
#include <jni.h>


namespace Caramel
{

namespace Android
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// JNI Method Core
//

class JniMethodCore
{
protected:

    JniMethodCore( jobject object, std::string&& methodName );
	
protected:

    void BuildMethod( const std::string& signature );

	std::string m_methodName;
	
	JNIEnv*   m_env { nullptr };
	jobject   m_object { nullptr };
	jmethodID m_methodId { nullptr };
};


///////////////////////////////////////////////////////////////////////////////
//
// JNI Method
//

template< typename Result >
class JniMethod : public JniMethodCore
{
public:

	JniMethod( jobject object, std::string&& methodName );


	// Call with no parameter
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
inline JniMethod< Result >::JniMethod( jobject object, std::string&& methodName )
	: JniMethodCore( object, std::move( methodName ))
{}


//
// Call Methods
//

template< typename Result >
inline Result JniMethod< Result >::Call()
{
	this->BuildMethod( MakeJniSignature< Result >() );
	return this->CallMethod();
}


template< typename Result >
template< typename... Args >
inline Result JniMethod< Result >::Call( const Args&... args )
{
	this->BuildMethod( MakeJniSignature< Result >( args... ));
	return this->CallMethod(
		( typename JniTypeTraits< Args >::Local( args, m_env )).Jni()... );
}


template< typename Result >
template< typename... JniArgs >
inline Result JniMethod< Result >::CallMethod( const JniArgs&... jniArgs )
{
	return JniTypeTraits< Result >::CallMethod( m_env, m_object, m_methodId, jniArgs... );
}




///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Android

} // namespace Caramel

#endif // __CARAMEL_ANDROID_DETAIL_JNI_METHOD_H
