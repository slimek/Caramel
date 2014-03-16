// Caramel C++ Library - I/O Facility - Text Reader Header

#ifndef __CARAMEL_IO_TEXT_READER_H
#define __CARAMEL_IO_TEXT_READER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


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
    // Read a line in UTF-8 encoded.
    // Returns false if EOF.
    //
    virtual Bool ReadLine( std::string& line ) = 0;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_TEXT_READER_H
