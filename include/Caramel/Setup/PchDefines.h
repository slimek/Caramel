// Caramel C++ Library - Libary Setup - Precompiled-Header Defines

#ifndef __CARAMEL_SETUP_PCH_DEFINES_H
#define __CARAMEL_SETUP_PCH_DEFINES_H

#include <Caramel/Setup/Compiler.h>
#include <Caramel/Setup/System.h>


///////////////////////////////////////////////////////////////////////////////
//
// Windows Settings
//

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

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

#endif // CARAMEL_SYSTEM_IS_WINDOWS


///////////////////////////////////////////////////////////////////////////////
//
// Microsoft Visual C++ Settings
//

#if defined( CARAMEL_COMPILER_IS_MSVC )

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif

#endif // CARAMEL_COMPILER_IS_MSVC


///////////////////////////////////////////////////////////////////////////////

#endif // __CARAMEL_SETUP_PCH_DEFINES_H
