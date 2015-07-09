// Caramel C++ Library - I/O Facility - Implementation

#include "CaramelPch.h"

#include "Io/MbcsStreamReader.h"
#include "Io/Utf16LeStreamReader.h"
#include "Io/Utf8StreamReader.h"
#include "Io/Utf8StreamWriter.h"
#include <Caramel/Io/BufferStream.h>
#include <Caramel/Io/FileStream.h>
#include <Caramel/Io/InputFileStream.h>
#include <Caramel/Io/InputMemoryStream.h>
#include <Caramel/Io/OutputFileStream.h>
#include <Caramel/Io/OutputMemoryStream.h>
#include <Caramel/Io/TextStreamReader.h>
#include <Caramel/Io/TextStreamWriter.h>
#include <cerrno>


namespace Caramel
{

//
// Contents
//
// < Constants >
//   ByteOrderMark
//   Newline
//
// < Streams >
//   FileStream
//   InputFileStream
//   OutputFileStream
//   InputMemoryStream
//   OutputMemoryStream
//   BufferStream
//
// < Reader/Writers >
//   TextStreamReader
//   MbcsStreamReader
//   Utf8StreamReader
//   TextStreamWriter
//   Utf8StreamWriter
//

///////////////////////////////////////////////////////////////////////////////
//
// Byte Order Mark (BOM)
// - Placed at the beginning of a Unicode text file.
//   Values are in little endian.
//

struct ByteOrderMark
{
    static std::string UTF16_LE() { return std::string( "\xFF\xFE" ); }
    static std::string UTF8()     { return std::string( "\xEF\xBB\xBF" ); }
};


///////////////////////////////////////////////////////////////////////////////
//
// Newline
// - Windows and Unix-like systems have different new line rule.
//

struct Newline
{
    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    static std::string UTF8() { return std::string( "\x0D\x0A" ); }
    #else
    static std::string UTF8() { return std::string( "\x0A" ); }
    #endif
};


///////////////////////////////////////////////////////////////////////////////
//
// File Stream
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


void FileStream::Open( const std::string& fileName )
{
    CARAMEL_CHECK_UTF8_ARGUMENT( u8FileName, fileName );

    this->Open( u8FileName );
}


void FileStream::Open( const Utf8String& fileName )
{
    if ( ! this->TryOpen( fileName ))
    {
        CARAMEL_THROW( "Open file \"{0}\" failed", fileName );
    }
}


Bool FileStream::TryOpen( const std::string& fileName )
{
    CARAMEL_CHECK_UTF8_ARGUMENT( u8FileName, fileName );

    return this->TryOpen( u8FileName );
}


Bool FileStream::TryOpen( const Utf8String& fileName )
{
    #if defined( CARAMEL_SYSTEM_IS_WINDOWS )
    {
        const Utf8String openMode( m_openMode );
        m_file = _wfopen( fileName.ToWstring().c_str(), openMode.ToWstring().c_str() );
    }
    #else
    {
        m_file = fopen( fileName.ToCstr(), m_openMode.c_str() );
    }
    #endif

    if ( m_file )
    {
        m_fileName = fileName.ToString();
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


InputFileStream::InputFileStream( const std::string& fileName )
    : FileStream( "rb" )
{
    CARAMEL_CHECK_UTF8_ARGUMENT( u8FileName, fileName );

    this->Open( u8FileName );
}


InputFileStream::InputFileStream( const Utf8String& fileName )
    : FileStream( "rb" )
{
    this->Open( fileName );
}


Usize InputFileStream::Read( Void* buffer, Usize size )
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
        CARAMEL_THROW( "fseek failed, error: {0}", strerror( errno ));
    }
}


Uint InputFileStream::Tell() const
{
    CARAMEL_ASSERT( m_file );

    const auto result = ftell( m_file );

    if ( 0 > result )
    {
        CARAMEL_THROW( "ftell failed, error: {0}", strerror( errno ));
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
// Output File Stream
//

OutputFileStream::OutputFileStream()
    : FileStream( "wb" )
{
}


OutputFileStream::OutputFileStream( const std::string& fileName )
    : FileStream( "wb" )
{
    CARAMEL_CHECK_UTF8_ARGUMENT( u8FileName, fileName );

    this->Open( u8FileName );
}


OutputFileStream::OutputFileStream( const Utf8String& fileName )
    : FileStream( "wb" )
{
    this->Open( fileName );
}


void OutputFileStream::Flush()
{
    CARAMEL_ASSERT( m_file );

    CARAMEL_VERIFY( 0 == fflush( m_file ));
}


void OutputFileStream::Write( const Void* data, Usize size )
{
    CARAMEL_ASSERT( m_file );

    const auto written = fwrite( data, 1, size, m_file );

    if ( written != size )
    {
        CARAMEL_THROW( "Write file \"{0}\" failed, errno: {1}", m_fileName, errno );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Input Memory Stream
//

InputMemoryStream::InputMemoryStream( const Void* buffer, Usize length )
    : m_buffer( static_cast< const Byte* >( buffer ))
    , m_length( length )
{}


Usize InputMemoryStream::Read( Void* buffer, Usize length )
{
    const Usize avails = m_length - m_position;
    Byte* dest = static_cast< Byte* >( buffer );

    if ( avails > length )
    {
        std::copy( &m_buffer[m_position], &m_buffer[m_position + length], dest );
        m_position += length;
        return length;
    }
    else
    {
        std::copy( &m_buffer[m_position], &m_buffer[m_position + avails], dest );
        m_position = m_length;
        return avails;
    }
}


void InputMemoryStream::Seek( Int offset )
{
    if ( offset > 0 )
    {
        const Usize uoffset = static_cast< Usize >( offset );

        const Usize avails = m_length - m_position;
        if ( uoffset < avails )
        {
            m_position += uoffset;
        }
        else
        {
            m_position = m_length;
        }
    }
    else
    {
        const Uint uoffset = static_cast< Uint >( - offset );
        if ( uoffset < m_position )
        {
            m_position -= uoffset;
        }
        else
        {
            m_position = 0;
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Output Memory Stream
//

OutputMemoryStream::OutputMemoryStream( Void* buffer, Usize length )
    : m_buffer( static_cast< Byte* >( buffer ))
    , m_length( length )
{}


void OutputMemoryStream::Write( const Void* data, Usize length )
{
    const Usize avails = m_length - m_position;
    const Byte* src = static_cast< const Byte* >( data );

    if ( avails > length )
    {
        std::copy( src, src + length, &m_buffer[ m_position ] );
        m_position += length;
    }
    else
    {
        CARAMEL_THROW( "Out of range, available: {0}, length: {1}", avails, length );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Buffer Stream
//

Usize BufferStream::Position() const
{
    return static_cast< Usize >( const_cast< std::stringstream& >( m_stream ).tellp() );
}


void BufferStream::Write( const Void* data, Usize size )
{
    m_stream.write( reinterpret_cast< const Char* >( data ), size );
    m_eof = false;
}


Usize BufferStream::Read( Void* buffer, Usize size )
{
    m_stream.read( reinterpret_cast< Char* >( buffer ), size );
    if ( m_stream )
    {
        return size;
    }
    else
    {
        const Usize count = static_cast< Usize >( m_stream.gcount() );
        m_stream.clear();
        m_eof = true;
        return count;
    }
}


Uint BufferStream::Tell() const
{
    return static_cast< Uint >( const_cast< std::stringstream& >( m_stream ).tellg() );
}


void BufferStream::Seek( Int offset )
{
    CARAMEL_NOT_IMPLEMENTED();
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
        Char bom[3] = { 0 };
        const auto count = m_stream.Peek( bom, 2 );

        if ( 2 == count && ByteOrderMark::UTF16_LE() == bom )
        {
            return TEXT_ENCODING_UTF16_LE;
        }
    }

    // Check 2 : UTF-8

    {
        Char bom[4] = { 0 };
        const auto count = m_stream.Peek( bom, 3 );

        if ( 3 == count && ByteOrderMark::UTF8() == bom )
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


Bool TextStreamReader::ReadLine( std::string& line )
{
    return m_reader->ReadLine( line );
}


std::string TextStreamReader::ReadAll()
{
    std::ostringstream builder;
    std::string line;
    Bool firstLine = true;

    while ( this->ReadLine( line ))
    {
        if ( firstLine )
        {
            firstLine = false;
        }
        else
        {
            builder << '\n';
        }

        builder << line;
    }

    return builder.str();
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


Bool MbcsStreamReader::ReadLine( std::string& line )
{
    if ( m_ended ) { return false; }

    const std::string chars = this->ReadCharLine();

    Utf8String u8Line;
    const Bool encoded = u8Line.TryParse( chars, m_encoding );
    if ( ! encoded )
    {
        CARAMEL_THROW( "Convert from encoding {0} failed", m_encoding );
    }

    line = u8Line.MoveString();
    return true;
}


std::string MbcsStreamReader::ReadCharLine()
{
    m_builder.str( "" );

    while ( true )
    {
        Char c = 0;
        const auto count = m_stream.Read( &c, 1 );
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


Bool Utf8StreamReader::ReadLine( std::string& line )
{
    if ( m_ended ) { return false; }

    std::string chars = this->ReadCharLine();

    if ( ! Utf8String::Validate( chars ))
    {
        CARAMEL_THROW( "Encoding is not UTF-8" );
    }

    line = std::move( chars );
    return true;
}


void Utf8StreamReader::TrySkipBom()
{
    Char bom[4] = { 0 };
    const auto count = m_stream.Read( bom, 3 );
    if ( 3 == count && ByteOrderMark::UTF8() == bom )
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
    : m_stream( stream )
    , m_ended( stream.IsEof() )

    // These two character are little endian
    , m_newline( "\x0A\x00" )  // U+000A
    , m_return ( "\x0D\x00" )  // U+000D
{

    this->TrySkipBom();
}


Bool Utf16LeStreamReader::ReadLine( std::string& line )
{
    if ( m_ended ) { return false; }

    m_builder.str( "" );

    while ( true )
    {
        Char c16[3] = { 0 };
        const auto count = m_stream.Read( &c16, 2 );
        if ( 2 != count )
        {
            if ( m_stream.IsEof() )
            {
                m_ended = true;
                break;
            }

            CARAMEL_THROW( "Read stream failed" );
        }

        if ( m_return  == c16 ) { continue; }
        if ( m_newline == c16 ) { break; }

        m_builder << c16[0] << c16[1];
    }

    Utf8String u8Line;
    const Bool encoded = u8Line.TryParse( m_builder.str(), TEXT_ENCODING_UTF16_LE );
    if ( ! encoded )
    {
        CARAMEL_THROW( "Convert UTF-16 LE to UTF-8 failed" );
    }

    line = u8Line.ToString();
    return true;
}


void Utf16LeStreamReader::TrySkipBom()
{
    Char bom[3] = { 0 };
    const auto count = m_stream.Read( bom, 2 );
    if ( 2 == count && ByteOrderMark::UTF16_LE() == bom )
    {
        return;  // the BOM is skipped.
    }

    // No BOM, move the read position back
    m_stream.Seek( - static_cast< Int >( count ));
}


///////////////////////////////////////////////////////////////////////////////
//
// Text Stream Writer
//

TextStreamWriter::TextStreamWriter( OutputStream& stream )
    : m_stream( stream )
    , m_writer( new Utf8StreamWriter( stream ))
{
}


void TextStreamWriter::Write( const std::string& text )
{
    CARAMEL_CHECK_UTF8_ARGUMENT( u8Text, text );

    this->Write( u8Text );
}


void TextStreamWriter::Write( const Utf8String& text )
{
    m_writer->Write( text );
}


void TextStreamWriter::WriteLine( const std::string& text )
{
    CARAMEL_CHECK_UTF8_ARGUMENT( u8Text, text );

    this->WriteLine( u8Text );
}


void TextStreamWriter::WriteLine( const Utf8String& text )
{
    m_writer->WriteLine( text );
}


///////////////////////////////////////////////////////////////////////////////
//
// UTF-8 Stream Writer
//

Utf8StreamWriter::Utf8StreamWriter( OutputStream& stream )
    : m_stream( stream )
{
    const std::string bom = ByteOrderMark::UTF8();
    m_stream.Write( bom.c_str(), bom.length() );
}


void Utf8StreamWriter::Write( const std::string& text )
{
    CARAMEL_CHECK_UTF8_ARGUMENT( u8Text, text );

    this->Write( u8Text );
}


void Utf8StreamWriter::Write( const Utf8String& text )
{
    m_stream.Write( text.ToCstr(), text.Length() );
}


void Utf8StreamWriter::WriteLine( const std::string& text )
{
    CARAMEL_CHECK_UTF8_ARGUMENT( u8Text, text );

    this->Write( u8Text );
}


void Utf8StreamWriter::WriteLine( const Utf8String& text )
{
    m_stream.Write( text.ToCstr(), text.Length() );

    const std::string newline = Newline::UTF8();
    m_stream.Write( newline.c_str(), newline.length() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel