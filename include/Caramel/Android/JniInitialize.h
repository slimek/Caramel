// Caramel C++ Library - Android Facility - JNI Base Header

#ifndef __CARAMEL_ANDROID_JNI_BASE_H
#define __CARAMEL_ANDROID_JNI_BASE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <jni.h>  // Java Native Interface


namespace Caramel
{

namespace Android
{

///////////////////////////////////////////////////////////////////////////////
//
// Stand-alone Functions
//

//
// JNI Initialize
// - Call this function in JNI_Load() to initialize Caramel JNI Facility.
//   You need to give a class path which is defined in your own project.
//   In Android, it is usually your main activity class.
//
void JniInitialize( JavaVM* jvm, const std::string& userClassPath );


///////////////////////////////////////////////////////////////////////////////

} // namespace Android

} // namespace Caramel

#endif // __CARAMEL_ANDROID_JNI_BASE_H
