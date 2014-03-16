// Caramel C++ Library - I/O Facility - MBCS Stream Reader Header

#ifndef __CARAMEL_IO_MBCS_STREAM_READER_H
#define __CARAMEL_IO_MBCS_STREAM_READER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Io/InputStream.h>
#include <Caramel/Io/TextReader.h>
#include <Caramel/String/TextEncoding.h>
#include <sstream>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// MBCS (Multi-Byte Character Set) Stream Reader
//

class MbcsStreamReader : public TextReader
{
public:

    MbcsStreamReader( InputStream& stream, TextEncoding encoding );


    //
    // Implements TextReader
    //

    Bool ReadLine( std::string& line );


protected:

    //
    // Read Char Line
    // - Read a line of chars, no matter of its encoding.
    //
    std::string ReadCharLine();


    InputStream& m_stream;
    Bool m_ended;


private:

    TextEncoding m_encoding;
    std::ostringstream m_builder;  // Build the input string
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_MBCS_STREAM_READER_H
