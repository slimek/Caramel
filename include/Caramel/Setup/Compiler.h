// Caramel C++ Library - Libary Setup - Compiler Determination

#ifndef __CARAMEL_SETUP_COMPILER_H
#define __CARAMEL_SETUP_COMPILER_H


///////////////////////////////////////////////////////////////////////////////
//
// Compiler - Microsoft Visual C++
//

#if defined( _MSC_VER )

#if ( 1800 > _MSC_VER )
#error "Caramel doesn't support Visual C++ before 2013"
#endif

#define CARAMEL_COMPILER_IS_MSVC

#define CARAMEL_COMPILER_NAME "Visual C++"


//
// Compiler Specific Syntax
//

#define CARAMEL_CURRENT_FUNCTION __FUNCTION__
#define CARAMEL_DEPRECATED __declspec( deprecated )


//
// Compiler Specific Implementation
//

// In Visual C++, long is an indivisial type.
// On the contrary, in GNU C++ and Clang, long is a typedef to int32 or int64.
#define CARAMEL_LONG_IS_INDIVIDUAL


//
// C++11 Compatibility
//

#if ( _MSC_VER >= 1900 )

#define CARAMEL_NOEXCEPT noexcept
#define CARAMEL_THREAD_LOCAL thread_local

#else

// Visual C++ 2013 limitations:
// - doesn't support noexcept
//   doesn't support thread_local, but have a workaround.

#define CARAMEL_NOEXCEPT 
#define CARAMEL_THREAD_LOCAL __declspec( thread )

#endif

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

#define CARAMEL_CURRENT_FUNCTION __PRETTY_FUNCTION__
#define CARAMEL_DEPRECATED
#define CARAMEL_NOEXCEPT noexcept
#define CARAMEL_THREAD_LOCAL thread_local

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

#define CARAMEL_CURRENT_FUNCTION __PRETTY_FUNCTION__
#define CARAMEL_DEPRECATED
#define CARAMEL_NOEXCEPT noexcept
#define CARAMEL_THREAD_LOCAL thread_local


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
