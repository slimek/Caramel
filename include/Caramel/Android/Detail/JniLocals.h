// Caramel C++ Library - Android Facility - Detail - JNI Local Wrappers Header

#ifndef __CARAMEL_ANDROID_DETAIL_JNI_LOCALS_H
#define __CARAMEL_ANDROID_DETAIL_JNI_LOCALS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <jni.h>
#include <boost/noncopyable.hpp>
#include <type_traits>


namespace Caramel
{

namespace Android
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// JNI Local Wrappers
// - RAII wrappers for JNI objects.
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


///////////////////////////////////////////////////////////////////////////////


}  // namespace Detali

}  // namespace Android

}  // namespace Caramel


#endif // __CARAMEL_ANDROID_DETAIL_JNI_LOCALS_H

