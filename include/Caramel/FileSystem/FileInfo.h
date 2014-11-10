// Caramel C++ Library - File System Facility - File Info Header

#ifndef __CARAMEL_FILE_SYSTEM_FILE_INFO_H
#define __CARAMEL_FILE_SYSTEM_FILE_INFO_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/FileSystem/Path.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// File Info
// - Immutable
//   Based on Boost.Filesystem library
//

class PathImpl;

class FileInfo
{
    friend class DirectoryInfo;

public:

    explicit FileInfo( const Path& path );

    
    /// Properties ///

    Bool Exists() const;

    Path GetPath() const;

	void Delete();

	void CopyTo( const Path& goalPath );

protected:

    explicit FileInfo( std::shared_ptr< PathImpl > path );

    std::shared_ptr< PathImpl > m_path;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_SYSTEM_FILE_INFO_H
