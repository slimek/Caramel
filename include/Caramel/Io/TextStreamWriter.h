// Caramel C++ Library - I/O Facility - Text Stream Writer Header

#ifndef __CARAMEL_IO_TEXT_STREAM_WRITER_H
#define __CARAMEL_IO_TEXT_STREAM_WRITER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Io/OutputStream.h>
#include <Caramel/Io/TextWriter.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Text Stream Writer
//

class TextStreamWriter : public TextWriter
{
public:

    //
    // Default text encoding: UTF-8
    // - This will write a BOM at the beginning automatically.
    //
    explicit TextStreamWriter( OutputStream& stream );


    //
    // Write a UTF-8 encoded string into stream.
    // - Throws if the text is not UTF-8 encoded.
    //
    void Write( const std::string& text ) override;
    void Write( const Utf8String& text ) override;


    //
    // Write a UTF-8 encoded string and a new line into stream.
    // - Throws if the text is not UTF-8 encoded.
    //
    void WriteLine( const std::string& text ) override;
    void WriteLine( const Utf8String& text ) override;


private:

    OutputStream& m_stream;
    std::unique_ptr< TextWriter > m_writer;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_TEXT_STREAM_WRITER_H
