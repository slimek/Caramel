// Caramel C++ Library - Windows Facility - Wide String Header

#ifndef __CARAMEL_WINDOWS_WIDE_STRING_H
#define __CARAMEL_WINDOWS_WIDE_STRING_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/String/TextEncoding.h>


namespace Caramel
{

namespace Windows
{

///////////////////////////////////////////////////////////////////////////////
//
// Wide String
// - A UTF-16 LE string based on std::wstring.
//

class WideString
{
public:

    WideString();
    WideString( const std::wstring& s );
    WideString( const std::string& input, TextEncoding encoding );

    static WideString FromUtf8( const std::string& input );


    /// Accessors ///

    const std::wstring ToString() const { return m_s; }
    const Wchar*       ToCstr()   const { return m_s.c_str(); }


    /// Conversions ///

    Bool TryParse( const std::string& input, TextEncoding encoding );

    std::string ToNarrow( TextEncoding encoding ) const;
    std::string ToUtf8() const;

    
private:

    std::wstring m_s;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Windows

} // namespace Caramel

#endif // __CARAMEL_WINDOWS_WIDE_STRING_H
