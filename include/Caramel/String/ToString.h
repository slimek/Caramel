// Caramel C++ Library - String Facility - To String Header

#ifndef __CARAMEL_STRING_TO_STRING_H
#define __CARAMEL_STRING_TO_STRING_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// To String Functions
// - Try to convert every thing to a string as possible.
//

//
// Primary templates
// - General rule needs x.ToString(), usually provided by StringConvertible.
//
template< typename T >
inline std::string ToString( const T& x )
{
    return x.ToString();
}


//
// Fundamental Overloadings
//

// Boolean: returns "true" or "false"
std::string ToString( Bool x );

// Integers
std::string ToString( Int16  x );
std::string ToString( Uint16 x );
std::string ToString( Int32  x );
std::string ToString( Uint32 x );
std::string ToString( Long   x );
std::string ToString( Ulong  x );
std::string ToString( Int64  x );
std::string ToString( Uint64 x );

// Floatings
std::string ToString( Float  x );
std::string ToString( Double x );


//
// Trivial Copy
//

inline const std::string& ToString( const std::string& x ) { return x; }
inline std::string&& ToString( std::string&& x ) { return std::move( x ); }


//
// C-style Strings
//

inline std::string ToString( const Char* sz ) { return std::string( sz ); }


///////////////////////////////////////////////////////////////////////////////
//
// To String Function Templates
// - Try to retrieve the name of types.
//

// Primary Template
// - Not defined by default.
template< typename T > std::string ToStringT();


//
// Fundamental Overloadings
//

// Integers
template<> std::string ToStringT< Bool >();
template<> std::string ToStringT< Char >();
template<> std::string ToStringT< Byte >();
template<> std::string ToStringT< Int16 >();
template<> std::string ToStringT< Uint16 >();
template<> std::string ToStringT< Int32 >();
template<> std::string ToStringT< Uint32 >();
template<> std::string ToStringT< Long >();
template<> std::string ToStringT< Ulong >();
template<> std::string ToStringT< Int64 >();
template<> std::string ToStringT< Uint64 >();

// Floatings
template<> std::string ToStringT< Float >();
template<> std::string ToStringT< Double >();


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_TO_STRING_H
