// Caramel C++ Library - String Facility - Algorithm Header

#ifndef __CARAMEL_STRING_ALGORITHM_H
#define __CARAMEL_STRING_ALGORITHM_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// String Predicates
//

// String : Char

Bool Contains( const std::string& s, Char c );

Bool EndsWith( const std::string& s, Char c );


/// Case insensitive ///

// String : String

Bool CainStartsWith( const std::string& input, const std::string& test );

Bool CainEquals( const std::string& input, const std::string& test );


///////////////////////////////////////////////////////////////////////////////
//
// String Extractors
//

std::string BeforeFirst( const std::string& s, Char c );

std::string AfterFirst( const std::string& s, Char c );


///////////////////////////////////////////////////////////////////////////////
//
// String Manipulators
//

void Trim( std::string& s );


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_ALGORITHM_H
