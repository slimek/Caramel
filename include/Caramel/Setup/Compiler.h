// Caramel C++ Library - Libary Setup - Compiler Determination

#ifndef __CARAMEL_SETUP_COMPILER_H
#define __CARAMEL_SETUP_COMPILER_H


///////////////////////////////////////////////////////////////////////////////
//
// Compiler - Microsoft Visual C++
//

#if defined( _MSC_VER )

#if ( _MSC_VER < 1900 )
#error "Caramel doesn't support Visual C++ before 2015"
#endif

#define CARAMEL_COMPILER_IS_MSVC

#define CARAMEL_COMPILER_NAME "Visual C++"


//
// Compiler Specific Syntax
//

#define CARAMEL_CURRENT_FUNCTION __FUNCTION__
#define CARAMEL_DEPRECATED __declspec( deprecated )


//
// Architecture
//

#if defined( _M_IX86 )

#define CARAMEL_ARCH_IS_X86
#define CARAMEL_ARCH_NAME "x86"

#define CARAMEL_SIZE_T_IS_UINT32

#elif defined( _M_X64 )

#define CARAMEL_ARCH_IS_X64
#define CARAMEL_ARCH_NAME "x64"

#define CARAMEL_SIZE_T_IS_UINT64

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


//
// Compiler Specific Syntax
//

#define CARAMEL_CURRENT_FUNCTION __PRETTY_FUNCTION__
#define CARAMEL_DEPRECATED __attribute__((deprecated))


//
// Compiler Specific Implementation
//

#define CARAMEL_SIZE_T_IS_UINT32

// For INT32_MIN and other limit defines
#define __STDC_LIMIT_MACROS


//
// Architecture
//

#if defined( __i386__ )

#define CARAMEL_ARCH_IS_X86
#define CARAMEL_ARCH_NAME "x86"

#elif defined( __arm__ )

#define CARAMEL_ARCH_IS_ARM
#define CARAMEL_ARCH_NAME "arm"

#endif


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


//
// Compiler Specific Syntax
//

#define CARAMEL_CURRENT_FUNCTION __PRETTY_FUNCTION__
#define CARAMEL_DEPRECATED __attribute__((deprecated))


//
// Compiler Specific Implementation
//

#define CARAMEL_SIZE_T_IS_ULONG

#if defined( __LP64__ )
#define CARAMEL_LONG_IS_64_BIT
#endif


//
// Architecture
//

#if defined( __i386__ )

#define CARAMEL_ARCH_IS_X86
#define CARAMEL_ARCH_NAME "x86"

#elif defined( __x86_64__ )

#define CARAMEL_ARCH_IS_X86_64
#define CARAMEL_ARCH_NAME "x86_64"

#elif defined( __arm__ )

#define CARAMEL_ARCH_IS_ARM
#define CARAMEL_ARCH_NAME "arm"

#elif defined( __arm64__ )

#define CARAMEL_ARCH_IS_ARM64
#define CARAMEL_ARCH_NAME "arm64"

#endif


#endif // Clang


///////////////////////////////////////////////////////////////////////////////
//
// Setup Validation
//

#if !defined( CARAMEL_COMPILER_NAME )
#error Other compilers are unsupported yet.
#endif

#if !defined( CARAMEL_ARCH_NAME )
#error Architecture not detected.
#endif


///////////////////////////////////////////////////////////////////////////////


#endif // __CARAMEL_SETUP_COMPILER_H
