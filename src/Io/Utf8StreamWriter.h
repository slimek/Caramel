// Caramel C++ Library - I/O Facility - UTF-8 Stream Writer Header

#ifndef __CARAMEL_IO_UTF8_STREAM_WRITER_H
#define __CARAMEL_IO_UTF8_STREAM_WRITER_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Io/OutputStream.h>
#include <Caramel/Io/TextWriter.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// UTF-8 Stream Writer
// - 
//

class Utf8StreamWriter : public TextWriter
{
public:

    Utf8StreamWriter( OutputStream& stream );


    //
    // Implements TextWriter
    //

    void Write( const std::string& text );
    void Write( const Utf8String& text );

    void WriteLine( const std::string& text );
    void WriteLine( const Utf8String& text );


private:

    OutputStream& m_stream;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_UTF8_STREAM_WRITER_H
