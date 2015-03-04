// Caramel C++ Library - Android Facility - Detail - JNI Local Wrappers Header

#ifndef __CARAMEL_ANDROID_DETAIL_JNI_LOCALS_H
#define __CARAMEL_ANDROID_DETAIL_JNI_LOCALS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <jni.h>
#include <boost/noncopyable.hpp>
#include <vector>


namespace Caramel
{

namespace Android
{

// Forwards declaration
class JniClass;
class JniObject;
class JniString;


namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// JNI Local Wrappers
// - RAII wrappers for JNI object local references.
//

//
// Fundamental Types
//
template< typename T >
class JniFundamentalLocal : public boost::noncopyable
{
public:
	JniFundamentalLocal( T value, JNIEnv* )
		: m_value( value )
	{}

	T Jni() const { return m_value; }

private:
	T m_value;
};


//
// String
// - Also provides conversion between std::string and jstring.
//
class JniStringLocal : public boost::noncopyable
{
public:
	JniStringLocal( const std::string& cs, JNIEnv* env );
	JniStringLocal( jstring js, JNIEnv* env );
	~JniStringLocal();

	jstring Jni() const { return m_jstring; }

	std::string ToString() const;

private:
	jstring m_jstring { nullptr };
	JNIEnv* m_env { nullptr };
};


//
// String Array
//
class JniStringArrayLocal : public boost::noncopyable
{
public:
	JniStringArrayLocal( const std::vector< std::string >& csa, JNIEnv* env );
	~JniStringArrayLocal();

	jobjectArray Jni() const { return m_jobjectArray; }

private:
	jobjectArray m_jobjectArray { nullptr };
	JNIEnv* m_env { nullptr };
};


//
// Object
//
class JniObjectLocal : public boost::noncopyable
{
public:
	JniObjectLocal( jobject obj, JNIEnv* evn );
	~JniObjectLocal();

	operator JniObject() const;
	jobject Jni() const { return m_jobject; }
	


private:
	jobject m_jobject { nullptr };
	JNIEnv* m_env { nullptr };
};


//
// Object Array
//
class JniObjectArrayLocal : public boost::noncopyable
{
public:
	JniObjectArrayLocal( jobjectArray objs, JNIEnv* env );
	~JniObjectArrayLocal();

	operator std::vector< JniObject >() const;

private:
	jobjectArray m_jobjectArray { nullptr };
	JNIEnv* m_env { nullptr };
};


//
// Class
//
class JniClassLocal : public boost::noncopyable
{
public:
	JniClassLocal( jobject obj, JNIEnv* env );
	~JniClassLocal();

	jclass Jni() const { return m_jclass; }

private:
	jclass m_jclass { nullptr };
	JNIEnv* m_env { nullptr };
};


///////////////////////////////////////////////////////////////////////////////

}  // namespace Detali

}  // namespace Android

}  // namespace Caramel

#endif // __CARAMEL_ANDROID_DETAIL_JNI_LOCALS_H

