// Caramel C++ Library - Windows Facility - File Info Header

#ifndef __CARAMEL_WINDOWS_FILE_INFO_H
#define __CARAMEL_WINDOWS_FILE_INFO_H
#pragma once

#include <Caramel/Caramel.h>


#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

#include <Caramel/FileSystem/FileInfo.h>


namespace Caramel
{

namespace Windows
{

///////////////////////////////////////////////////////////////////////////////
//
// File Info
// - Extend the common File Info with Windows specific issues.
//

class FileInfo : public Caramel::FileInfo
{
public:
    
    explicit FileInfo( const Path& path );

    
    //
    // Get Exact Path
    // - Win32 API treats paths as case insensitive, but NTFS is not.
    //   You may call this function to get a case sensitive path from NTFS.
    //   Throws if the path doesn't exist,
    //   therefore you should check the file by Exists() before this function.
    // 
    Path GetExactPath() const;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Windows

} // namespace Caramel

#endif // CARAMEL_SYSTEM_IS_WINDOWS

#endif // __CARAMEL_WINDOWS_FILE_INFO_H
