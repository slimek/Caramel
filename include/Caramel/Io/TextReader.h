// Caramel C++ Library - I/O Facility - Text Reader Header

#ifndef __CARAMEL_IO_TEXT_READER_H
#define __CARAMEL_IO_TEXT_READER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/String/Utf8String.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Text Reader
// - Interface
//

struct TextReader
{
    virtual ~TextReader() {}

    //
    // Read Line
    // - Returns false if EOF.
    //
    virtual Bool ReadLine( Utf8String& line ) = 0;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_TEXT_READER_H
