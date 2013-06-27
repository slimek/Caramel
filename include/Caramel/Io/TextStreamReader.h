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

#include <Caramel/Io/Detail/Utf8StreamReader.h>
#include <Caramel/Io/InputStream.h>
#include <Caramel/Io/TextReader.h>

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )
#include <Caramel/Io/Detail/MbcsStreamReader.h>
#endif



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
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_TEXT_STREAM_READER_H
