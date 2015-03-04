// Caramel C++ Library - Android Facility - Detail - JNI Global Wrappers Header

#ifndef __CARAMEL_ANDROID_DETAIL_JNI_GLOBALS_H
#define __CARAMEL_ANDROID_DETAIL_JNI_GLOBALS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <jni.h>
#include <boost/noncopyable.hpp>


namespace Caramel
{

namespace Android
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// JNI Global Wrappers
// - RAII wrappers for JNI object global references.
//

//
// Object
//
class JniObjectGlobal : public boost::noncopyable
{
public:
	JniObjectGlobal( jobject object );
	~JniObjectGlobal();

	jobject Jni() const { return m_object; }

private:
	jobject m_object { nullptr };
};


//
// Class
//
class JniClassGlobal : public boost::noncopyable
{
public:
	JniClassGlobal( jclass klass );
	~JniClassGlobal();

	jclass Jni() const { return m_class; }

private:
	jclass m_class { nullptr };
};


///////////////////////////////////////////////////////////////////////////////

}  // namespace Detali

}  // namespace Android

}  // namespace Caramel

#endif // __CARAMEL_ANDROID_DETAIL_JNI_GLOBALS_H
