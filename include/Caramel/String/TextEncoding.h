// Caramel C++ Library - String Facility - Text Encoding Header

#ifndef __CARAMEL_STRING_TEXT_ENCODING_H
#define __CARAMEL_STRING_TEXT_ENCODING_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


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
    TEXT_ENCODING_BIG5 = 950,
    TEXT_ENCODING_UTF8 = 65001,
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_TEXT_ENCODING_H
