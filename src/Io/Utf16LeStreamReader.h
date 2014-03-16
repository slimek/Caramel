// Caramel C++ Library - I/O Facility - UTF-16 LE Stream Reader Header

#ifndef __CARAMEL_IO_UTF16_LE_STREAM_READER_H
#define __CARAMEL_IO_UTF16_LE_STREAM_READER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Io/InputStream.h>
#include <Caramel/Io/TextReader.h>
#include <sstream>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// UTF-16 LE Stream Reader
//

class Utf16LeStreamReader : public TextReader
{
public:

    explicit Utf16LeStreamReader( InputStream& stream );


    //
    // Implements TextReader
    //

    Bool ReadLine( std::string& line );


private:

    void TrySkipBom();


    InputStream& m_stream;
    Bool m_ended;

    std::ostringstream m_builder;

    // UTF-16 LE characters

    std::string m_newline;  // LF U+000A
    std::string m_return;   // CR U+000D
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_UTF16_LE_STREAM_READER_H
