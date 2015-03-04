// Caramel C++ Library - Android Facility - Detail - JNI Type Traits Header

#ifndef __CARAMEL_ANDROID_DETAIL_JNI_TYPE_TRAITS_H
#define __CARAMEL_ANDROID_DETAIL_JNI_TYPE_TRAITS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Android/Detail/JniLocals.h>


namespace Caramel
{

namespace Android
{

// Forwards declaration
class JniObject;

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// JNI Type Traits
// - Supporting Types :
//   1. void
//   2. The fundamental types supported by JNI.
//   3. std::string and std::vector< std::string >
//   4. JniObject and std::vector< JniObject >
//

template< typename T >
struct JniTypeTraits;


//
// void
//

template<>
struct JniTypeTraits< void >
{
	static std::string Signature();  // "V"
	
	template< typename... Args >
	static void CallStaticMethod( JNIEnv* env, jclass cid, jmethodID mid, Args&&... args )
	{
		env->CallStaticVoidMethod( cid, mid, std::forward< Args >( args )... );
	}
};


//
// JNI Fundamental Types
//

template<>
struct JniTypeTraits< Bool >
{
	static std::string Signature();  // "Z"

	typedef JniFundamentalLocal< Bool > Local;

	template< typename... Args >
	static Bool CallStaticMethod( JNIEnv* env, jclass cid, jmethodID mid, Args&&... args )
	{
		return env->CallStaticBooleanMethod( cid, mid, std::forward< Args >( args )... );
	}
};


template<>
struct JniTypeTraits< Int >
{
	static std::string Signature();  // "I"

	typedef JniFundamentalLocal< Int > Local;
	
	template< typename... Args >
	static Int CallStaticMethod( JNIEnv* env, jclass cid, jmethodID mid, Args&&... args )
	{
		return env->CallStaticIntMethod( cid, mid, std::forward< Args >( args )... );
	}
};


template<>
struct JniTypeTraits< Int64 >
{
	static std::string Signature();  // "J"

	typedef JniFundamentalLocal< Int64 > Local;
	
	template< typename... Args >
	static Int64 CallStaticMethod( JNIEnv* env, jclass cid, jmethodID mid, Args&&... args )
	{
		return env->CallStaticLongMethod( cid, mid, std::forward< Args >( args )... );
	}
};


template<>
struct JniTypeTraits< Float >
{
	static std::string Signature();  // "D"

	typedef JniFundamentalLocal< Float > Local;
	
	template< typename... Args >
	static Float CallStaticMethod( JNIEnv* env, jclass cid, jmethodID mid, Args&&... args )
	{
		return env->CallStaticFloatMethod( cid, mid, std::forward< Args >( args )... );
	}
};


//
// std::string and relative types.
//

template<>
struct JniTypeTraits< std::string >
{
	static std::string Signature();  // "Ljava/lang/String;"

	typedef JniStringLocal Local;
	
	template< typename... Args >
	static std::string CallStaticMethod( JNIEnv* env, jclass cid, jmethodID mid, Args&&... args )
	{
		jstring jret = (jstring)env->CallStaticObjectMethod( cid, mid, std::forward< Args >( args )... );
		JniStringLocal local( jret, env );
		return local.ToString();
	}
};


template<>
struct JniTypeTraits< std::vector< std::string >>
{
	static std::string Signature();  // "[Ljava/lang/String;"
	
	typedef JniStringArrayLocal Local;
	
	template< typename... Args >
	static std::vector< std::string >
		CallStaticMethod( JNIEnv* env, jclass cid, jmethodID mid, Args&&... args )
	{
		jobjectArray jret =
			(jobjectArray)env->CallStaticObjectMethod( cid, mid, std::forward< Args >( args )... );
		JniStringArrayLocal local( jret, env );
		return local;
	}
};


//
// JniObject and relative types
//

template<>
struct JniTypeTraits< JniObject >
{
	static std::string Signature();  // "Ljava/lang/Object;"
	
	template< typename... Args >
	static JniObject
		CallStaticMethod( JNIEnv* env, jclass cid, jmethodID mid, Args&&... args );
};


template<>
struct JniTypeTraits< std::vector< JniObject >>
{
	static std::string Signature();  // "[Ljava/lang/Object;"
	
	typedef JniObjectArrayLocal Local;
	
	template< typename... Args >
	static std::vector< JniObject >
		CallStaticMethod( JNIEnv* env, jclass cid, jmethodID mid, Args&&... args );
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Android

} // namespace Caramel

#endif // __CARAMEL_ANDROID_DETAIL_JNI_TYPE_TRAITS_H
