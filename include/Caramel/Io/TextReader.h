// Caramel C++ Library - I/O Amenity - Text Reader Header

#ifndef __CARAMEL_IO_TEXT_READER_H
#define __CARAMEL_IO_TEXT_READER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


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
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_TEXT_READER_H
