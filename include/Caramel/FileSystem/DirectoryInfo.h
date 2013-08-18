// Caramel C++ Library - File System Facility - Directory Info Header

#ifndef __CARAMEL_FILE_SYSTEM_DIRECTORY_INFO_H
#define __CARAMEL_FILE_SYSTEM_DIRECTORY_INFO_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/FileSystem/Path.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Directory Info
// - Immutable
//   Based on Boost.Filesystem library
//

class DirectoryInfoImpl;

class DirectoryInfo
{
public:

    explicit DirectoryInfo( const Path& path );
    ~DirectoryInfo();


    /// Properties ///

    Bool Exists() const;


private:

    std::unique_ptr< DirectoryInfoImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_SYSTEM_DIRECTORY_INFO_H
