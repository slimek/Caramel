// Caramel C++ Library - File System Facility - Directory Info Private Header

#ifndef __CARAMEL_FILE_SYSTEM_DIRECTORY_INFO_IMPL_H
#define __CARAMEL_FILE_SYSTEM_DIRECTORY_INFO_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/FileSystem/DirectoryInfo.h>
#include <boost/filesystem.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Directory Info
//

class DirectoryInfoImpl
{
    friend class DirectoryInfo;

public:

    explicit DirectoryInfoImpl( const boost::filesystem::path& path );

private:

    boost::filesystem::path        m_path;
    boost::filesystem::file_status m_status;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_SYSTEM_DIRECTORY_INFO_IMPL_H
