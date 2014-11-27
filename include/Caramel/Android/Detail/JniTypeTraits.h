// Caramel C++ Library - Android Facility - Detail - JNI Type Traits Header

#ifndef __CARAMEL_ANDROID_DETAIL_JNI_TYPE_TRAITS_H
#define __CARAMEL_ANDROID_DETAIL_JNI_TYPE_TRAITS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


#if defined( CARAMEL_SYSTEM_IS_ANDROID )

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
};


//
// JNI Fundamental Types
//

template<>
struct JniTypeTraits< Bool >
{
	static std::string Signature();  // "Z"
};


template<>
struct JniTypeTraits< Int >
{
	static std::string Signature();  // "I"
};


template<>
struct JniTypeTraits< Int64 >
{
	static std::string Signature();  // "J"
};


template<>
struct JniTypeTraits< Float >
{
	static std::string Signature();  // "D"
};


//
// std::string and relative types.
//

template<>
struct JniTypeTraits< std::string >
{
	static std::string Signature();  // "Ljava/lang/String;"
};


//
// JniObject and relative types
//

template<>
struct JniTypeTraits< JniObject >
{
	static std::string Signature();  // "Ljava/lang/Object;"
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Android

} // namespace Caramel

#endif // CARAMEL_SYSTEM_IS_ANDROID

#endif // __CARAMEL_ANDROID_DETAIL_JNI_TYPE_TRAITS_H
