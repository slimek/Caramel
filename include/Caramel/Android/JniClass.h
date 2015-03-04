// Caramel C++ Library - Android Facility - JNI Class Header

#ifndef __CARAMEL_ANDROID_JNI_CLASS_H
#define __CARAMEL_ANDROID_JNI_CLASS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Android/Detail/JniConstructor.h>
#include <Caramel/Android/Detail/JniGlobals.h>
#include <Caramel/Android/Detail/JniStaticMethod.h>
#include <Caramel/Android/JniBase.h>
#include <Caramel/Android/JniObject.h>


namespace Caramel
{

namespace Android
{

///////////////////////////////////////////////////////////////////////////////
//
// JNI Class
//

class JniClass
{
public:

	explicit JniClass( std::string classPath );

	std::string Path() const { return m_classPath; }
	
	// Lazy initializing
	jclass Jni() const;


	// Make a static method to be called.
	template< typename Result >
	Detail::JniStaticMethod< Result > Method( std::string methodName ) const;


	// Create a new instance of this class
	template< typename... Args >
	JniObject NewObject( const Args&... args ) const;
	
	
private:

	std::string m_classPath;

	// Lazy initialized
	mutable std::shared_ptr< Detail::JniClassGlobal > m_class;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Result >
inline Detail::JniStaticMethod< Result > JniClass::Method( std::string methodName ) const
{
	return Detail::JniStaticMethod< Result >( this->Jni(), m_classPath, std::move( methodName ));
}


template< typename... Args >
inline JniObject JniClass::NewObject( const Args&... args ) const
{
	return Detail::JniConstructor( this->Jni(), m_classPath ).Call( args... );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Android

} // namespace Caramel

#endif // __CARAMEL_ANDROID_JNI_CLASS_H
