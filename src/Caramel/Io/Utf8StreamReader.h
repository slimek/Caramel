// Caramel C++ Library - I/O Facility - Detail - UTF-8 Stream Reader Header

#ifndef __CARAMEL_IO_DETAIL_UTF8_STREAM_READER_H
#define __CARAMEL_IO_DETAIL_UTF8_STREAM_READER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Io/InputStream.h>
#include <Caramel/Io/TextReader.h>
#include <sstream>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// UTF-8 Stream Reader
//

class Utf8StreamReader : public TextReader
{
public:

    explicit Utf8StreamReader( InputStream& stream );


    //
    // Implements TextReader
    //

    Bool ReadLine( Utf8String& line );


private:

    void TrySkipBom();

    InputStream& m_stream;

    std::ostringstream m_builder;  // Build the input string
    Bool m_ended;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline Utf8StreamReader::Utf8StreamReader( InputStream& stream )
    : m_stream( stream )
    , m_ended( stream.IsEof() )
{
    this->TrySkipBom();
}


inline Bool Utf8StreamReader::ReadLine( Utf8String& line )
{
    if ( m_ended ) { return false; }

    m_builder.str( "" );

    while ( true )
    {
        Char c = 0;
        const Uint count = m_stream.Read( &c, 1 );
        if ( 1 != count )
        {
            if ( m_stream.IsEof() )
            {
                m_ended = true;
                break;
            }

            CARAMEL_THROW( "Read stream failed" );
        }

        if ( '\r' == c ) { continue; }
        if ( '\n' == c ) { break; }

        m_builder << c;
    }

    const Bool encoded = line.TryParse( m_builder.str() );
    if ( ! encoded )
    {
        CARAMEL_THROW( "Encoding is not UTF-8" );
    }

    return true;
}


inline void Utf8StreamReader::TrySkipBom()
{
    Uint32 bom = 0;
    const Uint count = m_stream.Read( &bom, 3 );
    if ( 3 == count && UNICODE_BOM_UTF8 == bom )
    {
        return;  // the BOM is skipped
    }

    // No BOM, move the read position back
    m_stream.Seek( - static_cast< Int >( count ));
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_IO_DETAIL_UTF8_STREAM_READER_H
