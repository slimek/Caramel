// Caramel C++ Library - I/O Facility - Detail - UTF-16 LE Stream Reader Header

#ifndef __CARAMEL_IO_DETAIL_UTF16_LE_STREAM_READER_H
#define __CARAMEL_IO_DETAIL_UTF16_LE_STREAM_READER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Io/InputStream.h>
#include <Caramel/Io/TextReader.h>


namespace Caramel
{

namespace Detail
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

    Bool ReadLine( Utf8String& line );

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline Utf16LeStreamReader::Utf16LeStreamReader( InputStream& stream )
{
}


inline Bool Utf16LeStreamReader::ReadLine( Utf8String& line )
{
    CARAMEL_NOT_IMPLEMENTED();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_IO_DETAIL_UTF16_LE_STREAM_READER_H
