// Caramel C++ Library - File System Facility - Directory Info Header

#ifndef __CARAMEL_FILE_SYSTEM_DIRECTORY_INFO_H
#define __CARAMEL_FILE_SYSTEM_DIRECTORY_INFO_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/FileSystem/Path.h>
#include <vector>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Directory Info
// - Immutable
//   Based on Boost.Filesystem library
//

class FileInfo;
class PathImpl;

class DirectoryInfo
{
public:

    /// Creators ///

    explicit DirectoryInfo( const Path& path );

    // Returns the current working directory.
    static DirectoryInfo Current();


    /// Properties ///

    Bool Exists() const;

    Path GetPath() const;


    // Get all sub-directories in this directory
    std::vector< DirectoryInfo > GetDirectories() const;

    // Get all files in this directory
    std::vector< FileInfo > GetFiles() const;

    // Get all files in this directory and all its sub-directories
    std::vector< FileInfo > GetFilesRecursively() const;


    /// Operations ///

    // If the directory already exists, this method do nothing.
    // Throws if the directory cannot be created.
    void Create();

    // Throws if the directory cannot be deleted. This includes:
    // - It is not found.
    //   It is not empty.
    //   You don't have the permission.
    void Delete();

	// Delete the directory
    boost::uintmax_t DeleteAll();

private:

    explicit DirectoryInfo( std::shared_ptr< PathImpl > path );

    template< typename Value, typename Iterator >
    std::vector< Value > Traverse( Bool ) const;

    std::shared_ptr< PathImpl > m_path;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_SYSTEM_DIRECTORY_INFO_H
