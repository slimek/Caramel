// Caramel C++ Library - Starting Header

#ifndef __CARAMEL_CARAMEL_H
#define __CARAMEL_CARAMEL_H

#include <Caramel/Setup/Compiler.h>
#include <Caramel/Setup/System.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

// mandatory ANSI C++ 11 headers
#include <cstdint>
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

typedef std::int8_t     Int8;
typedef std::int16_t    Int16;
typedef std::int32_t    Int32;
typedef std::int64_t    Int64;

typedef std::uint8_t    Uint8;
typedef std::uint16_t   Uint16;
typedef std::uint32_t   Uint32;
typedef std::uint64_t   Uint64;


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
