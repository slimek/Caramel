// Caramel C++ Library - String Facility - UTF-8 String Header

#ifndef __CARAMEL_STRING_UTF8_STRING_H
#define __CARAMEL_STRING_UTF8_STRING_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/String/CodedString.h>
#include <Caramel/String/StringConvertible.h>


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

class Utf8String : public CodedString
                 , public StringConvertible< Utf8String >
{
public:
    
    Utf8String();

    // Throws if 'text' is not UTF-8 encoded.
    explicit Utf8String( const std::string& u8Text );

    //
    // Construct from another coding
    // - Throws if 'text' can't be converted to UTF-8 by the specified encoding.
    //

    explicit Utf8String( const CodedString& text );

    Utf8String( const std::string& text, TextEncoding encoding );

    
    //
    // Conversions
    //
    
    //
    // Returns whether the input string is UTF-8 encoded.
    // NOTES: An ASCII string would also satisfy the UTF-8 rule. 
    //

    Bool TryParse( const std::string& u8Text );

    // convert from binary data
    Bool TryParse( const Byte* data, Uint length );


    std::string ToString() const { return *this; }

    // NOTE: No implicit conversion to std::string.
    //       Always use Utf8String as possible.

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline Utf8String::Utf8String()
    : CodedString( TEXT_ENCODING_UTF8 )
{}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_UTF8_STRING_H
