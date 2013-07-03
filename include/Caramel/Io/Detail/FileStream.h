// Caramel C++ Library - I/O Amenity - Detail - File Stream Header

#ifndef __CARAMEL_IO_DETAIL_FILE_STREAM_H
#define __CARAMEL_IO_DETAIL_FILE_STREAM_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Error/Exception.h>
#include <Caramel/String/Utf8String.h>
#include <cstdio>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// File Stream
// - 
//

class FileStream
{
public:

    void Open( const Utf8String& fileName );
    Bool TryOpen( const Utf8String& fileName );

    void Close();

    Bool IsOpen() const { return nullptr != m_file; }


protected:

    explicit FileStream( const std::string& openMode );
    ~FileStream();


    FILE* m_file;

    Utf8String m_openMode;
    Utf8String m_fileName;

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline FileStream::FileStream( const std::string& openMode )
    : m_file( nullptr )
    , m_openMode( openMode )
{
}


inline FileStream::~FileStream()
{
    this->Close();
}


inline void FileStream::Open( const Utf8String& fileName )
{
    if ( ! this->TryOpen( fileName ))
    {
        CARAMEL_THROW( "Open file failed: %s", fileName );
    }
}



inline Bool FileStream::TryOpen( const Utf8String& fileName )
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


inline void FileStream::Close()
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

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_IO_DETAIL_FILE_STREAM_H
