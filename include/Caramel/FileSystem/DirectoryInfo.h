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

    Bool Exists()  const;
    Path GetPath() const;


    /// Directory / File Iteration ///

    // Get all sub-directories in this directory
    std::vector< DirectoryInfo > GetDirectories() const;

	// Get all sub-directories in this directory and all its sub-directories
	std::vector< DirectoryInfo > GetDirectoriesRecursively() const;

    // Get all files in this directory
    std::vector< FileInfo > GetFiles() const;

    // Get all files in this directory and all its sub-directories
    std::vector< FileInfo > GetFilesRecursively() const;


    /// Operations ///

    // If the directory already exists, this method do nothing.
    // Throws if the directory cannot be created.
    void Create();

	// Copy all file to goalPath. Goal directory can't exist. 
    // Throws if any file copy failed.
	void CopyAllTo( const Path& goalPath ) const;

	// Copy directory to goalPath. 
	// Throws if goal directory exist.
	void CopyTo( const Path& goalPath ) const;

	// Move directory to goalPath.
	// Throws if goal directory exist.
	void Rename( const Path& goalPath );

    // Delete this directory
    // - Throws if the directory cannot be deleted. This includes:
    //     You don't have the permission.  -> boost::filesystem::filesystem_error
    //     It is not empty.                -> boost::filesystem::filesystem_error
    //     It is not found.                -> Caramel::Exception
    void Delete();

	// Delete this directory, recursively
    // - Throws if the directory cannot be deleted. This includes:
    //     You don't have the permission.  -> boost::filesystem::filesystem_error
    //     It is not found.                -> Caramel::Exception
    void DeleteAll();


private:

    explicit DirectoryInfo( std::shared_ptr< PathImpl > path );

    template< typename Value, typename Iterator >
    std::vector< Value > Traverse( Bool ) const;

    std::shared_ptr< PathImpl > m_path;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_SYSTEM_DIRECTORY_INFO_H
