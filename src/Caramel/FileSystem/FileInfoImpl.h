// Caramel C++ Library - File System Facility - File Info Private Header

#ifndef __CARAMEL_FILE_SYSTEM_FILE_INFO_IMPL_H
#define __CARAMEL_FILE_SYSTEM_FILE_INFO_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/FileSystem/FileInfo.h>
#include <boost/filesystem.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// File Info
//

class FileInfoImpl
{
public:

    explicit FileInfoImpl( const boost::filesystem::path& path );

private:

    boost::filesystem::path        m_path;
    boost::filesystem::file_status m_status;

    friend class FileInfo;

};

///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_SYSTEM_FILE_INFO_IMPL_H
