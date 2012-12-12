//
// Caramel C++ Library
//
// Setup - Compiler Determination
//

#ifndef __CARAMEL_SETUP_COMPILER_H
#define __CARAMEL_SETUP_COMPILER_H


///////////////////////////////////////////////////////////////////////////////
//
// Compiler - Microsoft Visual C++
//

#if defined( _MSC_VER )

#if ( 1700 > _MSC_VER )
#error "Caramel doesn't support Visual C++ before 2012"
#endif

#define CARAMEL_COMPILER_IS_MSVC

// compiler settings
#define CARAMEL_COMPILER_HAS_PRAGMA_ONCE
#define CARAMEL_STDCALL      __stdcall
#define CARAMEL_CDECL        __cdecl
#define CARAMEL_DEPRECATED   __declspec( deprecated )

#endif // Visual C++


///////////////////////////////////////////////////////////////////////////////
//
// Setup Validation
//

#if !defined( CARAMEL_COMPILER_IS_MSVC )
#error Other compilers are unsupported yet.
#endif


///////////////////////////////////////////////////////////////////////////////


#endif // __CARAMEL_SETUP_COMPILER_H
