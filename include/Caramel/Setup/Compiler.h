// Caramel C++ Library - Libary Setup - Compiler Determination

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

#define CARAMEL_COMPILER_NAME "Visual C++"


// Compiler settings

#define CARAMEL_STDCALL      __stdcall
#define CARAMEL_CDECL        __cdecl
#define CARAMEL_DEPRECATED   __declspec( deprecated )


#endif // Visual C++


///////////////////////////////////////////////////////////////////////////////
//
// Compiler - GNU C++
//

#if defined( __GNUC__ ) && !defined( __clang__ )

#if ( 4 > __GNUC__ ) || (( 4 == __GNUC__ ) && 7 > __GNUC_MINOR__ )
#error "Caramel doesn't support GNU C++ before 4.7"
#endif

#define CARAMEL_COMPILER_IS_GCC

#define CARAMEL_COMPILER_NAME "GNU C++"


// Compiler settings

#define CARAMEL_STDCALL    __attribute__(( stdcall ))
#define CARAMEL_CDECL      __attribute__(( cdecl ))
#define CARAMEL_DEPRECATED

// For INT32_MIN and other limit defines
#define __STDC_LIMIT_MACROS


#endif // GNU C++


///////////////////////////////////////////////////////////////////////////////
//
// Compiler - Clang / LLVM
//

#if defined( __clang__ )

#if ( 3 > __clang_major__ ) || (( 3 == __clang_major__ ) && ( 1 > __clang_minor__ ))
#error "Caramel doesn't support Clang before 3.1"
#endif

#define CARAMEL_COMPILER_IS_CLANG

#define CARAMEL_COMPILER_NAME "Clang"


// Compiler settings

#define CARAMEL_STDCALL
#define CARAMEL_CDECL
#define CARAMEL_DEPRECATED


#endif // Clang


///////////////////////////////////////////////////////////////////////////////
//
// Setup Validation
//

#if !defined( CARAMEL_COMPILER_NAME )
#error Other compilers are unsupported yet.
#endif


///////////////////////////////////////////////////////////////////////////////


#endif // __CARAMEL_SETUP_COMPILER_H
