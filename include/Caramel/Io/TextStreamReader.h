// Caramel C++ Library - I/O Amenity - Text Stream Reader Header

//
// USAGE:
//
// TextStreamReader can detect the text encoding of a stream.
// 
// On Windows, it supports 2 encodings:
// - If a file starts with a UTF-8 BOM, it is UTF-8
//   Otherwise uses Windows ACP to convert it into UTF-8.
//
// On other operating system, it treats stream as UTF-8 in default,
// no matter whether the stream has a UTF-8 BOM or not.
//
// NOTES:
// - On Windows, you may specify the encoding code page explicitly.
//

#ifndef __CARAMEL_IO_TEXT_STREAM_READER_H
#define __CARAMEL_IO_TEXT_STREAM_READER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Error/Assert.h>
#include <Caramel/Io/Detail/MbcsStreamReader.h>
#include <Caramel/Io/Detail/Utf16LeStreamReader.h>
#include <Caramel/Io/Detail/Utf8StreamReader.h>
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


private:

    TextEncoding DetectEncoding();
    void BuildReader( TextEncoding encoding );

    InputStream& m_stream;

    std::unique_ptr< TextReader > m_reader;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline TextStreamReader::TextStreamReader( InputStream& stream )
    : m_stream( stream )
{
    this->BuildReader( this->DetectEncoding() );
}


inline TextStreamReader::TextStreamReader( InputStream& stream, TextEncoding encoding )
    : m_stream( stream )
{
    this->BuildReader( encoding );
}


inline TextEncoding TextStreamReader::DetectEncoding()
{
    CARAMEL_ASSERT( 0 == m_stream.Tell() );

    // Check 1 : UTF-16 LE

    {
        Uint16 bom = 0;
        const Uint count = m_stream.Peek( &bom, 2 );

        if ( 2 == count && UNICODE_BOM_UTF16_LE == bom )
        {
            return TEXT_ENCODING_UTF16_LE;
        }
    }

    // Check 2 : UTF-8

    {
        Uint32 bom = 0;
        const Uint count = m_stream.Peek( &bom, 3 );

        if ( 3 == count && UNICODE_BOM_UTF8 == bom )
        {
            return TEXT_ENCODING_UTF8;
        }
    }

    // Otherwise

    return TEXT_ENCODING_DEFAULT;
}


inline void TextStreamReader::BuildReader( TextEncoding encoding )
{
    switch ( encoding )
    {
    case TEXT_ENCODING_UTF8:
        m_reader.reset( new Detail::Utf8StreamReader( m_stream ));
        return;

    case TEXT_ENCODING_UTF16_LE:
        m_reader.reset( new Detail::Utf16LeStreamReader( m_stream ));
        return;

    default:
        m_reader.reset( new Detail::MbcsStreamReader( m_stream, encoding ));
    }
}


inline Bool TextStreamReader::ReadLine( Utf8String& line )
{
    return m_reader->ReadLine( line );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_TEXT_STREAM_READER_H
