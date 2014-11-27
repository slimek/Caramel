// Caramel C++ Library - Android Facility - Detail - JNI Signature Header

#ifndef __CARAMEL_ANDROID_DETAIL_JNI_SIGNATURE_H
#define __CARAMEL_ANDROID_DETAIL_JNI_SIGNATURE_H
#pragma once


#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Android/Detail/JniTypeTraits.h>
#include <Caramel/String/Format.h>


#if defined( CARAMEL_SYSTEM_IS_ANDROID )

namespace Caramel
{

namespace Android
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// JNI Signature
//

template< typename Result >
std::string MakeJniSignature();

template< typename Result, typename... Args >
std::string MakeJniSignature( const Args&... args );


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T >
inline std::string BuildJniSignature( const T& a )
{
	return JniTypeTraits< T >::Signature();
}


template< typename T, typename... Args >
inline std::string BuildJniSignature( const T& a, const Args&... args )
{
	return JniTypeTraits< T >::Signature() + BuildJniSignature( args... );
}


template< typename Result >
inline std::string MakeJniSignature()
{
	return Format( "(){0}", JniTypeTraits< Result >::Signature() );
}


template< typename Result, typename... Args >
inline std::string MakeJniSignature( const Args&... args )
{
	return Format(
		"({0}){1}", BuildJniSignature( args... ), JniTypeTraits< Result >::Signature() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Android

} // namespace Caramel

#endif // CARAMEL_SYSTEM_IS_ANDROID

#endif // __CARAMEL_ANDROID_DETAIL_JNI_SIGNATURE_H
