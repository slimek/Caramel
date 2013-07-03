// Caramel C++ Library - I/O Amenity - Input File Stream Header

#ifndef __CARAMEL_IO_INPUT_FILE_STREAM_H
#define __CARAMEL_IO_INPUT_FILE_STREAM_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Error/Assert.h>
#include <Caramel/Io/Detail/FileStream.h>
#include <Caramel/Io/InputStream.h>
#include <Caramel/String/Utf8String.h>
#include <cerrno>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Input File Stream
//

class InputFileStream : public Detail::FileStream
                      , public InputStream
{
public:

    InputFileStream();

    explicit InputFileStream( const Utf8String& fileName );


    //
    // InputStream implements
    //

    Uint Read( Void* buffer, Uint size );

    void Seek( Int offset );

    Uint Tell() const;

    Bool IsEof() const;

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline InputFileStream::InputFileStream()
    : FileStream( "rb" )
{
}


inline InputFileStream::InputFileStream( const Utf8String& fileName )
    : FileStream( "rb" )
{
    this->Open( fileName );
}


inline Uint InputFileStream::Read( Void* buffer, Uint size )
{
    CARAMEL_ASSERT( m_file );
    
    return fread( buffer, 1, size, m_file );
}


inline void InputFileStream::Seek( Int offset )
{
    CARAMEL_ASSERT( m_file );

    const Int result = fseek( m_file, offset, SEEK_CUR );

    if ( 0 != result )
    {
        CARAMEL_THROW( "fseek failed, error: %s", strerror( errno ));
    }
}


inline Uint InputFileStream::Tell() const
{
    CARAMEL_ASSERT( m_file );

    const Int result = ftell( m_file );

    if ( 0 > result )
    {
        CARAMEL_THROW( "ftell failed, error: %s", strerror( errno ));
    }

    return static_cast< Uint >( result );
}


inline Bool InputFileStream::IsEof() const
{
    if ( ! m_file ) { return true; }

    return 0 != feof( m_file );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_INPUT_FILE_STREAM_H
