// Caramel C++ Library - Libary Setup - System Determination

#ifndef __CARAMEL_SETUP_SYSTEM_H
#define __CARAMEL_SETUP_SYSTEM_H


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
// System - Android
//

#if defined( ANDROID ) || defined( __ANDROID )

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
