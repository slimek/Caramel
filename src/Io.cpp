// Caramel C++ Library - I/O Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Io/Detail/MbcsStreamReader.h>
#include <Caramel/Io/Detail/Utf16LeStreamReader.h>
#include <Caramel/Io/Detail/Utf8StreamReader.h>
#include <Caramel/Io/InputFileStream.h>
#include <Caramel/Io/TextStreamReader.h>
#include <cerrno>


namespace Caramel
{

//
// Contents
//
// 1. InputFileStream
// 2. TextStreamReader
//

///////////////////////////////////////////////////////////////////////////////
//
// Input File Stream
//

InputFileStream::InputFileStream()
    : FileStream( "rb" )
{
}


InputFileStream::InputFileStream( const Utf8String& fileName )
    : FileStream( "rb" )
{
    this->Open( fileName );
}


Uint InputFileStream::Read( Void* buffer, Uint size )
{
    CARAMEL_ASSERT( m_file );
    
    return fread( buffer, 1, size, m_file );
}


void InputFileStream::Seek( Int offset )
{
    CARAMEL_ASSERT( m_file );

    const Int result = fseek( m_file, offset, SEEK_CUR );

    if ( 0 != result )
    {
        CARAMEL_THROW( "fseek failed, error: %s", strerror( errno ));
    }
}


Uint InputFileStream::Tell() const
{
    CARAMEL_ASSERT( m_file );

    const Int result = ftell( m_file );

    if ( 0 > result )
    {
        CARAMEL_THROW( "ftell failed, error: %s", strerror( errno ));
    }

    return static_cast< Uint >( result );
}


Bool InputFileStream::IsEof() const
{
    if ( ! m_file ) { return true; }

    return 0 != feof( m_file );
}


///////////////////////////////////////////////////////////////////////////////
//
// Text Stream Reader
//

TextStreamReader::TextStreamReader( InputStream& stream )
    : m_stream( stream )
{
    this->BuildReader( this->DetectEncoding() );
}


TextStreamReader::TextStreamReader( InputStream& stream, TextEncoding encoding )
    : m_stream( stream )
{
    this->BuildReader( encoding );
}


TextEncoding TextStreamReader::DetectEncoding()
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


void TextStreamReader::BuildReader( TextEncoding encoding )
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


Bool TextStreamReader::ReadLine( Utf8String& line )
{
    return m_reader->ReadLine( line );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel