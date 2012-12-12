//
// Caramel C++ Library
//
// String Facility - String Header
//
//   Based on std::string, encoding is not specified.
//

#ifndef __CARAMEL_STRING_STRING_H
#define __CARAMEL_STRING_STRING_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/String/BasicString.h>
#include <Caramel/String/CharTraits.h>
#include <Caramel/String/StringConvertible.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// String
// - A lightweight wrapper of std::string
//

class String : public BasicString< std::string, CharTraits< Char > >
             , public StringConvertible< String >
{
    typedef BasicString< std::string, CharTraits< Char > > Inherited;

public:

    /// Constructors ///

    String() {}

    String( const std::string& s )
        : Inherited( s )
    {}

    String( const String& s )
        : Inherited( s )
    {}

    String( const Char* sz )
        : Inherited( std::string( sz ))
    {}


    /// Conversions ///

    operator std::string() const { return *this; }
    std::string ToString() const { return *this; }

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_STRING_H
