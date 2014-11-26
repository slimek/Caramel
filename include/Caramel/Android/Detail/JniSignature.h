// Caramel C++ Library - Android Facility - Detail - JNI Signature Header

#ifndef __CARAMEL_ANDROID_DETAIL_JNI_SIGNATURE_H
#define __CARAMEL_ANDROID_DETAIL_JNI_SIGNATURE_H
#pragma once


#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Android/Detail/JniTypeTraits.h>


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

template< typename R >
std::string MakeJniSignature();

template< typename R, typename... Args >
std::string MakeJniSignature();



///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Android

} // namespace Caramel

#endif // CARAMEL_SYSTEM_IS_ANDROID

#endif // __CARAMEL_ANDROID_DETAIL_JNI_SIGNATURE_H
