// Caramel C++ Library - I/O Facility - Detail - MBCS Stream Reader Header

#ifndef __CARAMEL_IO_DETAIL_MBCS_STREAM_READER_H
#define __CARAMEL_IO_DETAIL_MBCS_STREAM_READER_H

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
// MBCS (Multi-Byte Character Set) Stream Reader
//

class MbcsStreamReader : public TextReader
{
public:

    MbcsStreamReader( InputStream& stream, TextEncoding encoding );


    //
    // Implements TextReader
    //

    Bool ReadLine( Utf8String& line );


private:

    InputStream& m_stream;
    TextEncoding m_encoding;

    std::ostringstream m_builder;  // Build the input string
    Bool m_ended;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline MbcsStreamReader::MbcsStreamReader( InputStream& stream, TextEncoding encoding )
    : m_stream( stream )
    , m_encoding( encoding )
    , m_ended( stream.IsEof() )
{
}


inline Bool MbcsStreamReader::ReadLine( Utf8String& line )
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

    const Bool encoded = line.TryParse( m_builder.str(), m_encoding );
    if ( ! encoded )
    {
        CARAMEL_THROW( "Convert from encoding %u failed", m_encoding );
    }

    return true;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_IO_DETAIL_MBCS_STREAM_READER_H
