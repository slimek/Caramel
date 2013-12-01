// Caramel C++ Library - I/O Facility - UTF-8 Stream Reader Header

#ifndef __CARAMEL_IO_UTF8_STREAM_READER_H
#define __CARAMEL_IO_UTF8_STREAM_READER_H
#pragma once

#include <Caramel/Caramel.h>
#include "Io/MbcsStreamReader.h"


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// UTF-8 Stream Reader
//

class Utf8StreamReader : public MbcsStreamReader
{
public:

    explicit Utf8StreamReader( InputStream& stream );

    //
    // Implements TextReader ( Overwrites MbcsStreamReader )
    //

    Bool ReadLine( std::string& line );


private:

    void TrySkipBom();

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_UTF8_STREAM_READER_H
