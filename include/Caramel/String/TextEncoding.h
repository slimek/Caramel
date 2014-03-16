// Caramel C++ Library - String Facility - Text Encoding Header

#ifndef __CARAMEL_STRING_TEXT_ENCODING_H
#define __CARAMEL_STRING_TEXT_ENCODING_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Text Encoding
// - To specity text coding of a string or byte stream.
//   Values are according to Windows code pages.
//

enum TextEncoding
{
    TEXT_ENCODING_BIG5      = 950,
    TEXT_ENCODING_UTF8      = 65001,

    TEXT_ENCODING_UTF16_LE  = 1200,


    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )

    // In Windows, call ::GetACP() to get the current active code page.
    TEXT_ENCODING_WINDOWS_ACP = 0,

    TEXT_ENCODING_DEFAULT = TEXT_ENCODING_WINDOWS_ACP,

    #else

    // In other systems, the default encoding is UTF-8.
    TEXT_ENCODING_DEFAULT = TEXT_ENCODING_UTF8,

    #endif

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_TEXT_ENCODING_H
