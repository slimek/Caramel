// Caramel C++ Library - Android Facility - JNI Class Header

#ifndef __CARAMEL_ANDROID_JNI_CLASS_H
#define __CARAMEL_ANDROID_JNI_CLASS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
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
	

	/// Make static methods ///

	template< typename Result >
	Detail::JniStaticMethod< Result > Method( std::string methodName ) const;


private:

	std::string m_classPath;

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Result >
inline Detail::JniStaticMethod< Result > JniClass::Method( std::string methodName ) const
{
	return Detail::JniStaticMethod< Result >( m_classPath, std::move( methodName ));
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Android

} // namespace Caramel

#endif // __CARAMEL_ANDROID_JNI_CLASS_H
