// Caramel C++ Library - I/O Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Io/FileStream.h>
#include <Caramel/Io/InputFileStream.h>
#include <Caramel/Io/MbcsStreamReader.h>
#include <Caramel/Io/TextStreamReader.h>
#include <Caramel/Io/Utf16LeStreamReader.h>
#include <Caramel/Io/Utf8StreamReader.h>
#include <cerrno>


namespace Caramel
{

//
// Contents
//
// < Streams >
//   FileStream
//   InputFileStream
//
// < Readers >
//   TextStreamReader
//   MbcsStreamReader
//   Utf8StreamReader
//

///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

FileStream::FileStream( const std::string& openMode )
    : m_file( nullptr )
    , m_openMode( openMode )
{
}


FileStream::~FileStream()
{
    this->Close();
}


void FileStream::Open( const Utf8String& fileName )
{
    if ( ! this->TryOpen( fileName ))
    {
        CARAMEL_THROW( "Open file failed: %s", fileName );
    }
}



Bool FileStream::TryOpen( const Utf8String& fileName )
{
    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    {
        m_file = _wfopen( fileName.ToWstring().c_str(), m_openMode.ToWstring().c_str()  );
    }
    #else
    {
        m_file = fopen( fileName.ToCstr(), m_openMode.ToCstr() );
    }
    #endif

    if ( m_file )
    {
        m_fileName = fileName;
        return true;
    }
    else
    {
        return false;
    }
}


void FileStream::Close()
{
    if ( ! m_file ) { return; }

    const Int result = fclose( m_file );
    m_file = nullptr;

    if ( 0 != result )
    {
        // TODO: Trace Warning.
    }
}


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
        m_reader.reset( new Utf8StreamReader( m_stream ));
        return;

    case TEXT_ENCODING_UTF16_LE:
        m_reader.reset( new Utf16LeStreamReader( m_stream ));
        return;

    default:
        m_reader.reset( new MbcsStreamReader( m_stream, encoding ));
    }
}


Bool TextStreamReader::ReadLine( Utf8String& line )
{
    return m_reader->ReadLine( line );
}


///////////////////////////////////////////////////////////////////////////////
//
// MBCS Stream Reader
//

MbcsStreamReader::MbcsStreamReader( InputStream& stream, TextEncoding encoding )
    : m_stream( stream )
    , m_encoding( encoding )
    , m_ended( stream.IsEof() )
{
}


Bool MbcsStreamReader::ReadLine( Utf8String& line )
{
    if ( m_ended ) { return false; }

    const std::string chars = this->ReadCharLine();

    const Bool encoded = line.TryParse( chars, m_encoding );
    if ( ! encoded )
    {
        CARAMEL_THROW( "Convert from encoding %u failed", m_encoding );
    }

    return true;
}


std::string MbcsStreamReader::ReadCharLine()
{
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

    return m_builder.str();
}


///////////////////////////////////////////////////////////////////////////////
//
// UTF-8 Stream Reader
//

Utf8StreamReader::Utf8StreamReader( InputStream& stream )
    : MbcsStreamReader( stream, TEXT_ENCODING_UTF8 )
{
    this->TrySkipBom();
}


Bool Utf8StreamReader::ReadLine( Utf8String& line )
{
    if ( m_ended ) { return false; }

    const std::string chars = this->ReadCharLine();

    const Bool encoded = line.TryParse( chars );
    if ( ! encoded )
    {
        CARAMEL_THROW( "Encoding is not UTF-8" );
    }

    return true;
}


void Utf8StreamReader::TrySkipBom()
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
//
// UTF-16 LE Stream Reader
//

Utf16LeStreamReader::Utf16LeStreamReader( InputStream& stream )
{
}


Bool Utf16LeStreamReader::ReadLine( Utf8String& line )
{
    CARAMEL_NOT_IMPLEMENTED();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel