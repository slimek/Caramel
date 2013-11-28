// Caramel C++ Library - String Facility - To String Header

#ifndef __CARAMEL_STRING_TO_STRING_H
#define __CARAMEL_STRING_TO_STRING_H
#pragma once

#include <Caramel/Caramel.h>


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
std::string ToString( Int64  x );
std::string ToString( Uint64 x );

// Floatings
std::string ToString( Float  x );
std::string ToString( Double x );


//
// Trivial Copy
//

inline std::string ToString( const std::string& x ) { return x; }


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_TO_STRING_H
