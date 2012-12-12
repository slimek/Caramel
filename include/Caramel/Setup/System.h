//
// Caramel C++ Library
//
// Setup - System Determination
//

#ifndef __CARAMEL_SETUP_SYSTEM_H
#define __CARAMEL_SETUP_SYSTEM_H


///////////////////////////////////////////////////////////////////////////////
//
// System - Windows
//

#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ )

#define ISHTAR_SYSTEM_IS_WINDOWS

// exclude min/max macros in <windef.h> of Windows Platform SDK
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
// Setup Validation
//

#if !defined( ISHTAR_SYSTEM_IS_WINDOWS )
#error Other operation systems are unsupported yet.
#endif


///////////////////////////////////////////////////////////////////////////////

#endif // __CARAMEL_SETUP_SYSTEM_H
