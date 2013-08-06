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

class AnsiString : public BasicString< AnsiString, std::string, CharTraits< Char > >
                 , public StringConvertible< AnsiString >
{
    friend class BasicString< AnsiString, std::string, CharTraits< Char > >;

public:

    /// Constructors ///

    AnsiString();
    AnsiString( const std::string& s );
    AnsiString( const AnsiString& s );

    template< Uint n >
    AnsiString( const Char(& sz)[n] );


    /// Conversions ///

    operator std::string() const { return m_s; }
    std::string ToString() const { return m_s; }

private:

    /// Date Members ///

    std::string m_s;

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementations
//

AnsiString::AnsiString()
{}


AnsiString::AnsiString( const std::string& s )
    : m_s( s )
{}


AnsiString::AnsiString( const AnsiString& s )
    : m_s( s )
{}


template< Uint n >
AnsiString::AnsiString( const Char(& sz)[n] )
    : m_s( sz, sz + n )
{}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_ANSI_STRING_H
