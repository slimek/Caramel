// Caramel C++ Library - Android Facility - Detail - JNI Method Header

#ifndef __CARAMEL_ANDROID_DETAIL_JNI_METHOD_H
#define __CARAMEL_ANDROID_DETAIL_JNI_METHOD_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

namespace Android
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// JNI Method Core
//

class JniMethodCore
{
protected:

};


///////////////////////////////////////////////////////////////////////////////
//
// JNI Method
//

template< typename Result >
class JniMethod : public JniMethodCore
{
public:

	JniMethod( std::string classPath, std::string methodName );


	// Call with no parameter
	Result Call();

	template< typename... Args >
	Result Call( const Args&... args );

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Android

} // namespace Caramel

#endif // __CARAMEL_ANDROID_DETAIL_JNI_METHOD_H
