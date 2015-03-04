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

    JniMethodCore( std::string&& classPath, std::string&& methodName );
	
protected:

    void BuildMethod( const std::string& signature );

    std::string m_classPath;
	std::string m_methodName;
	
	JNIEnv*   m_env { nullptr };
	jclass    m_class { nullptr };
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

	JniMethod( std::string classPath, std::string methodName );


	// Call with no parameter
	Result Call();

	template< typename... Args >
	Result Call( const Args&... args );


private:
    
	template< typename... JniArgs >
	Result CallMethod( const JniArgs... jniArgs );
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Android

} // namespace Caramel

#endif // __CARAMEL_ANDROID_DETAIL_JNI_METHOD_H
