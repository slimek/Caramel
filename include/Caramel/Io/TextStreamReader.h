// Caramel C++ Library - I/O Facility - Text Stream Reader Header

#ifndef __CARAMEL_IO_TEXT_STREAM_READER_H
#define __CARAMEL_IO_TEXT_STREAM_READER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Io/InputStream.h>
#include <Caramel/Io/TextReader.h>
#include <Caramel/String/TextEncoding.h>
#include <Caramel/String/Utf8String.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Text Stream Reader
//
// USAGE:
//
// TextStreamReader can detect the text encoding of a stream.
// 
// On Windows, it supports 3 encodings:
// - File starts with a UTF-8 BOM     => UTF-8
//   File starts with a UTF-16 LE BOM => UTF-16 LE
//   Otherwise uses Windows ACP
//
// On other operating system, it treats stream as UTF-8 in default,
// no matter whether the stream has a UTF-8 BOM or not.
//
// NOTES:
// - On Windows, you may specify the encoding code page explicitly.
//

class TextStreamReader : public TextReader
{
public:

    explicit TextStreamReader( InputStream& stream );

    TextStreamReader( InputStream& stream, TextEncoding encoding );


    //
    // Read Line
    // - Returns false if EOF.
    //
    Bool ReadLine( Utf8String& line );

    //
    // Read All
    // - Read until the end of stream in a single string.
    //
    Utf8String ReadAll();


private:

    TextEncoding DetectEncoding();
    void BuildReader( TextEncoding encoding );

    InputStream& m_stream;

    std::unique_ptr< TextReader > m_reader;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_TEXT_STREAM_READER_H
