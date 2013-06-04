// Caramel C++ Library - String Facility - Coded String Header

#ifndef __CARAMEL_STRING_CODED_STRING_H
#define __CARAMEL_STRING_CODED_STRING_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/String/BasicString.h>
#include <Caramel/String/CharTraits.h>
#include <Caramel/String/TextEncoding.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Coded String
// - A lightweight wrapper of std::string, MBCS encoding specified.
//   When assign strings between different encodings, a conversion would be applied.
//
//   CodedString is not String Convertible.
//   If you want to output it, please convert it to a Utf8String explicitly.
//

class CodedString : public BasicString< std::string, CharTraits< Char > >
{
    typedef BasicString< std::string, CharTraits< Char > > Inherited;

public:
    explicit CodedString( TextEncoding encoding );
    CodedString( const std::string& text, TextEncoding encoding );

private:
    TextEncoding m_encoding;
};


//
// Compiled-time determined
//

template< TextEncoding encoding >
class CodedStringN : public CodedString
{
public:
    CodedStringN();
    explicit CodedStringN( const std::string& text );

    // Auto conversions
    CodedStringN( const CodedString& cstring );
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementations
//

inline CodedString::CodedString( TextEncoding encoding )
    : m_encoding( encoding )
{}


inline CodedString::CodedString( const std::string& text, TextEncoding encoding )
    : Inherited( text )
    , m_encoding( encoding )
{}


template< TextEncoding encoding >
inline CodedStringN< encoding >::CodedStringN()
    : CodedString( encoding )
{}


template< TextEncoding encoding >
inline CodedStringN< encoding >::CodedStringN( const std::string& text )
    : CodedString( text, encoding )
{}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_CODED_STRING_H
