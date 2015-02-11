// Caramel C++ Library - Android Facility - JNI Center Header

#ifndef __CARAMEL_ANDROID_JNI_CENTER_H
#define __CARAMEL_ANDROID_JNI_CENTER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Object/FacilityLongevity.h"
#include <Caramel/Object/Singleton.h>
#include <jni.h>


namespace Caramel
{

namespace Android
{

///////////////////////////////////////////////////////////////////////////////
//
// JNI Center
//

class JniCenter : public Singleton< JniCenter, FACILITY_LONGEVITY_JNI_CENTER >
{
public:

	~JniCenter();

	void Initialize( JavaVM* vm, const std::string& userClassPath );

	// Get the JNIEnv object of the current thread.
	JNIEnv* GetEnvOfCurrentThread();

	jclass GetClassId( const std::string& classPath );


private:

	JavaVM* m_jvm { nullptr };

	// This is a global JNI object.
	jobject m_classLoader { nullptr };

	jmethodID m_findClassMethod { nullptr };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Android

} // namespace Caramel

#endif // __CARAMEL_ANDROID_JNI_CENTER_H

