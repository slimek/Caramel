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

    Bool  Exists()  const;
    Path  GetPath() const;

    // Throws if the file is greater than UINT32_MAX bytes.
    Uint32 Size() const;

    Uint64 Size64() const;


    /// Operations ///

	void CopyTo( const Path& goalPath ) const;

	void Delete();


protected:

    explicit FileInfo( std::shared_ptr< PathImpl > path );

    std::shared_ptr< PathImpl > m_path;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_SYSTEM_FILE_INFO_H
