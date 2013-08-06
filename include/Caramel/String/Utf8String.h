// Caramel C++ Library - String Facility - UTF-8 String Header

#ifndef __CARAMEL_STRING_UTF8_STRING_H
#define __CARAMEL_STRING_UTF8_STRING_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/String/BasicString.h>
#include <Caramel/String/CharTraits.h>
#include <Caramel/String/StringConvertible.h>
#include <Caramel/String/TextEncoding.h>
#include <boost/operators.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// UTF-8 String
// - A specialized string in UTF-8 encoding.
//   All constructors and assignment would checking the encoding to ensure
//   the input text is correct UTF-8 encoded.
//   This is the default string type of all Caramel I/O components.
//

class Utf8String : public BasicString< Utf8String, std::string, CharTraits< Char > >
                 , public StringConvertible< Utf8String >
                 , public boost::addable< Utf8String >
{
    friend class BasicString< Utf8String, std::string, CharTraits< Char > >;

public:
    
    Utf8String();

    explicit Utf8String( Char c );

    // Throws if 'text' is not UTF-8 encoded.
    explicit Utf8String( const std::string& u8Text );

    //
    // Construct from another coding
    // - Throws if 'text' can't be converted to UTF-8 by the specified encoding.
    //

    Utf8String( const std::string& text, TextEncoding encoding );


    //
    // Operators
    //

    Utf8String& operator+=( const Utf8String& rhs );


    //
    // Conversions
    //
    
    //
    // Returns whether the input string is UTF-8 encoded.
    // NOTES: An ASCII string would also satisfy the UTF-8 rule. 
    //
    Bool TryParse( const std::string& u8Text );

    // convert from other encoding
    Bool TryParse( const std::string& text, TextEncoding encoding );

    // convert from binary data, which should be a UTF-8 text.
    Bool TryParse( const Byte* data, Uint length );


    std::string ToString() const { return m_s; }

    // Cooperates with C-style functions
    const Char* ToCstr() const { return m_s.c_str(); }

    // NOTE: No implicit conversion to std::string.
    //       Always use Utf8String as possible.


private:
    
    /// Data Members ///

    std::string m_s;


#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

public:

    //
    // Windows Specific
    // - In Windows, many APIs use wide string, in UTF-16 LE encoding.
    //   Here provides some wstring conversions to cooperate with Windows APIs.
    //
    //   In other OS, like Linux or Mac, you should never use wstring...
    //   

    //
    // Construct from a wstring
    // - Suppose the wText is UTF-16 LE encoded.
    //   Throws is conversion failed.
    //
    explicit Utf8String( const std::wstring& wText );

    // Convert to UTF-16 LE wstring
    std::wstring ToWstring() const;


#endif // CARAMEL_SYSTEM_IS_WINDOWS

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_UTF8_STRING_H
