// Caramel C++ Library - Android Facility - JNI Object Header

#ifndef __CARAMEL_ANDROID_JNI_OBJECT_H
#define __CARAMEL_ANDROID_JNI_OBJECT_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Android/Detail/JniMethod.h>
#include <Caramel/Android/JniBase.h>


namespace Caramel
{

namespace Android
{

///////////////////////////////////////////////////////////////////////////////
//
// JNI Object
//

class JniObject
{
public:

	JniObject() {}
	JniObject( jobject obj, JNIEnv* env );

	Bool  GetBool( const std::string& fieldName ) const;
	Int   GetInt ( const std::string& fieldName ) const;
	Int64 GetLong( const std::string& fieldName ) const;
	
	std::string GetString( const std::string& fieldName ) const;


	/// Make methods ///

	template< typename Result >
	Detail::JniMethod< Result > Method( std::string methodName );


private:

	template< typename T >
	jfieldID GetFieldId( const std::string& fieldName ) const;

	std::shared_ptr< Detail::JniObjectLocal > m_object;
	std::shared_ptr< Detail::JniClassLocal >  m_class;
	JNIEnv* m_env { nullptr };
};


///////////////////////////////////////////////////////////////////////////////
//
// JNI Type Tratis with JniObject
//

namespace Detail
{

template< typename... Args >
inline JniObject JniTypeTraits< JniObject >::
    CallStaticMethod( JNIEnv* env, jclass cid, jmethodID mid, Args&&... args )
{
	jobject jret = env->CallStaticObjectMethod( cid, mid, std::forward< Args >( args )... );
	JniObjectLocal local( jret, env );
	return local;
}


template< typename... Args >
inline std::vector< JniObject > JniTypeTraits< std::vector< JniObject >>::
	CallStaticMethod( JNIEnv* env, jclass cid, jmethodID mid, Args&&... args )
{
	jobjectArray jret =
		(jobjectArray)env->CallStaticObjectMethod( cid, mid, std::forward< Args >( args )... );
	JniObjectArrayLocal local( jret, env );
	return local;
}


} // namespace Detail

///////////////////////////////////////////////////////////////////////////////

} // namespace Android

} // namespace Caramel

#endif // __CARAMEL_ANDROID_JNI_OBJECT_H
