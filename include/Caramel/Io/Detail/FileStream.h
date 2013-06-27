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
    void Close();

    Bool IsOpen() const;


protected:

    explicit FileStream( std::string openMode );
    ~FileStream();


    FILE* m_file;

    std::string m_openMode;
    Utf8String  m_fileName;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline void FileStream::Open( const Utf8String& fileName )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_IO_DETAIL_FILE_STREAM_H
