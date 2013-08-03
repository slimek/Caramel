// Caramel C++ Library - File System Facility - File Info Header

#ifndef __CARAMEL_FILE_SYSTEM_FILE_INFO_H
#define __CARAMEL_FILE_SYSTEM_FILE_INFO_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/FileSystem/Path.h>
#include <Caramel/String/Utf8String.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// File Info
// - Immutable
//   Based on Boost.Filesystem library
//

class FileInfoImpl;

class FileInfo
{
public:

    explicit FileInfo( const Path& path );
    ~FileInfo();

    
    //
    // Accessors
    //

    Path GetPath() const;

    Bool Exists() const;

protected:

    std::unique_ptr< FileInfoImpl > m_impl;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_SYSTEM_FILE_INFO_H
