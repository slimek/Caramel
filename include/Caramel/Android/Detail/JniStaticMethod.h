// Caramel C++ Library - Android Facility - Detail - JNI Static Method Header

#ifndef __CARAMEL_ANDROID_DETAIL_JNI_STATIC_METHOD_H
#define __CARAMEL_ANDROID_DETAIL_JNI_STATIC_METHOD_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Android/Detail/JniTypeTraits.h>
#include <Caramel/Android/Detail/JniSignature.h>


#if defined( CARAMEL_SYSTEM_IS_ANDROID )

namespace Caramel
{

namespace Android
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// JNI Static Method Core
//

class JniStaticMethodCore
{
protected:

	JniStaticMethodCore( std::string&& classPath, std::string&& methodName );


private:

	std::string m_classPath;
	std::string m_methodName;
};


///////////////////////////////////////////////////////////////////////////////
//
// JNI Static Method
//

template< typename Result >
class JniStaticMethod : public JniStaticMethodCore
{
public:

	JniStaticMethod( std::string classPath, std::string methodName );


	// Call with no parameter.
	Result Call();

	template< typename... Args >
	Result Call( const Args&... args );
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename Result >
inline JniStaticMethod< Result >::JniStaticMethod( std::string classPath, std::string methodName )
	: JniStaticMethodCore( std::move( classPath ), std::move( methodName ))
{}


//
// Call Methods
//

template< typename Result >
inline Result JniStaticMethod< Result >::Call()
{
	const auto signature = MakeJniSignature< Result >();
	return Result();
}


template< typename Result >
template< typename... Args >
inline Result JniStaticMethod< Result >::Call( const Args&... args )
{
	const auto signature = MakeJniSignature< Result, Args... >();
	return Result();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Android

} // namespace Caramel

#endif // CARAMEL_SYSTEM_IS_ANDROID

#endif // __CARAMEL_ANDROID_DETAIL_JNI_STATIC_METHOD_H
