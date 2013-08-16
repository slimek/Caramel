// Caramel C++ Library - I/O Facility - File Stream Header

#ifndef __CARAMEL_IO_FILE_STREAM_H
#define __CARAMEL_IO_FILE_STREAM_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/String/Utf8String.h>
#include <cstdio>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// File Stream
//

class FileStream
{
public:

    void Open( const std::string& fileName );
    void Open( const Utf8String&  fileName );

    Bool TryOpen( const std::string& fileName );
    Bool TryOpen( const Utf8String&  fileName );

    void Close();

    Bool IsOpen() const { return nullptr != m_file; }


protected:

    explicit FileStream( const std::string& openMode );
    ~FileStream();


    FILE* m_file;

    std::string m_openMode;
    std::string m_fileName;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_FILE_STREAM_H
