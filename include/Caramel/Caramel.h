//
// Caramel C++ Library
//
// Starting Header
//

#ifndef __CARAMEL_CARAMEL_H
#define __CARAMEL_CARAMEL_H

#include <Caramel/Setup/System.h>
#include <Caramel/Setup/Compiler.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

// mandatory ANSI C++ 11 headers
#include <cstdlib>
#include <memory>
#include <string>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Fundamental Typedefs
//

/// Integers ///

typedef bool    Bool;
typedef char    Char;
typedef wchar_t Wchar, WideChar;
typedef short   Short;
typedef int     Int;
typedef long    Long;

typedef unsigned char   Byte;
typedef unsigned int    Uint;


/// Integers with Bits Specified ///

#if defined( CARAMEL_COMPILER_IS_MSVC )

typedef __int8  Int8;
typedef __int16 Int16;
typedef __int32 Int32;
typedef __int64 Int64;

typedef unsigned __int8  Uint8;
typedef unsigned __int16 Uint16;
typedef unsigned __int32 Uint32;
typedef unsigned __int64 Uint64;


#endif


/// Floating Points ///

typedef float  Float;
typedef double Double;


/// Others ///

typedef void Void;   // only for a typeless pointer, void*   


///////////////////////////////////////////////////////////////////////////////
//
// Basic Template Types
//

struct NullType;
struct EmptyType {};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_CARAMEL_H
