// Caramel C++ Library - String Facility - Ansi String Header

#ifndef __CARAMEL_STRING_ANSI_STRING_H
#define __CARAMEL_STRING_ANSI_STRING_H

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
// Ansi String
// - A lightweight wrapper of std::string, encoding unspecified.
//   For UTF-8 encoded text, use Utf8String.
//

class AnsiString : public BasicString< std::string, CharTraits< Char > >
                 , public StringConvertible< AnsiString >
{
    typedef BasicString< std::string, CharTraits< Char > > Inherited;

public:

    /// Constructors ///

    AnsiString();
    AnsiString( const std::string& s );
    AnsiString( const AnsiString& s );

    template< Uint n >
    AnsiString( const Char(& sz)[n] );


    /// Conversions ///

    operator std::string() const { return *this; }
    std::string ToString() const { return *this; }

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementations
//

AnsiString::AnsiString()
{}


AnsiString::AnsiString( const std::string& s )
    : Inherited( s )
{}


AnsiString::AnsiString( const AnsiString& s )
    : Inherited( s )
{}


template< Uint n >
AnsiString::AnsiString( const Char(& sz)[n] )
    : Inherited( std::string( sz, sz + n ))
{}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_ANSI_STRING_H
