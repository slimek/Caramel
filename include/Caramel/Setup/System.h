// Caramel C++ Library - Libary Setup - System Determination

#ifndef __CARAMEL_SETUP_SYSTEM_H
#define __CARAMEL_SETUP_SYSTEM_H


#if !defined( CARAMEL_COMPILER_NAME )
#error "Compiler must be detected first"
#endif

///////////////////////////////////////////////////////////////////////////////
//
// System - Windows
//

#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ )

#define CARAMEL_SYSTEM_IS_WINDOWS

#define CARAMEL_SYSTEM_NAME "Windows"


// Exclude min/max macros in <windef.h> of Windows Platform SDK

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif


#endif  // Windows


///////////////////////////////////////////////////////////////////////////////
//
// System - iOS
//

#if ( defined( CARAMEL_COMPILER_IS_GCC ) || defined( CARAMEL_COMPILER_IS_CLANG ))

#include <TargetConditionals.h>

#if( defined( TARGET_OS_IPHONE ) || defined( TARGET_IPHONE_SIMULATOR ))

#define CARAMEL_SYSTEM_IS_IOS

#define CARAMEL_SYSTEM_NAME "iOS"

#endif

#endif // iOS

///////////////////////////////////////////////////////////////////////////////
//
// System - Android
//

#if defined( ANDROID ) || defined( __ANDROID__ )

#define CARAMEL_SYSTEM_IS_ANDROID

#define CARAMEL_SYSTEM_NAME "Android"


#endif // Android


///////////////////////////////////////////////////////////////////////////////
//
// Setup Validation
//

#if !defined( CARAMEL_SYSTEM_NAME )
#error Other operation systems are unsupported yet.
#endif


///////////////////////////////////////////////////////////////////////////////

#endif // __CARAMEL_SETUP_SYSTEM_H
