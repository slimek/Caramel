// Caramel C++ Library - Windows Facility - Wide String Header

#ifndef __CARAMEL_WINDOWS_WIDE_STRING_H
#define __CARAMEL_WINDOWS_WIDE_STRING_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

#include <Caramel/String/BasicString.h>
#include <Caramel/String/CharTraits.h>
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

class WideString : public BasicString< WideString, std::wstring, CharTraits< Wchar > >
{
    

public:

    WideString();
    WideString( const std::string& input, TextEncoding encoding );

    Bool TryParse( const std::string& input, TextEncoding encoding );

    std::string ToNarrow( TextEncoding encoding ) const;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Windows

} // namespace Caramel

#endif // CARAMEL_SYSTEM_IS_WINDOWS

#endif // __CARAMEL_WINDOWS_WIDE_STRING_H
