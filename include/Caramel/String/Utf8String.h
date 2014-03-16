// Caramel C++ Library - String Facility - UTF-8 String Header

#ifndef __CARAMEL_STRING_UTF8_STRING_H
#define __CARAMEL_STRING_UTF8_STRING_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Error/Exception.h>
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
//

class Utf8String : public StringConvertible< Utf8String >
                 , public boost::addable< Utf8String >
{
public:
    
    Utf8String();

    explicit Utf8String( Char c );

    //
    // Throws if 'text' is not UTF-8 encoded.
    //
    explicit Utf8String( const std::string& u8Text );

    //
    // Construct from another encoding
    // - Throws if 'text' can't be converted to UTF-8 by the specified encoding.
    //
    Utf8String( const std::string& text, TextEncoding encoding );


    /// Properties ///

    Uint Length() const { return static_cast< Uint >( m_s.length() ); }


    /// Operators ///

    Utf8String& operator+=( const Utf8String& rhs );


    /// Conversions ///

    //
    // Tests if the input string is UTF-8 encoded    
    //
    Bool TryParse( const std::string& u8Text );

    //
    // Converts from other encoding
    //
    Bool TryParse( const std::string& text, TextEncoding encoding );

    //
    // Converts from binary data, which should be a UTF-8 text
    //
    Bool TryParse( const Byte* data, Uint length );


    std::string ToString() const { return m_s; }

    // Cooperates with C-style functions
    const Char* ToCstr() const { return m_s.c_str(); }

    // NOTE: No implicit conversion to std::string,
    //       which may cause overloading ambiguity.


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
    //   In other OS, like Linux or Mac, you should NEVER use wstring...
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


} // namespace Caramel

///////////////////////////////////////////////////////////////////////////////
//
// Macros
//

#define CARAMEL_CHECK_UTF8_ARGUMENT( u8str, str ) \
    Caramel::Utf8String u8str; \
    if ( ! u8str.TryParse( str )) \
    { \
        CARAMEL_THROW( #str " is not UTF-8 encoded" ); \
    }


///////////////////////////////////////////////////////////////////////////////

#endif // __CARAMEL_STRING_UTF8_STRING_H
