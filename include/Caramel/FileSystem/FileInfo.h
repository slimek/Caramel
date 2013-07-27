// Caramel C++ Library - File System Amenity - File Info Header

#ifndef __CARAMEL_FILE_SYSTEM_FILE_INFO_H
#define __CARAMEL_FILE_SYSTEM_FILE_INFO_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/FileSystem/Path.h>
#include <Caramel/String/Utf8String.h>
#include <boost/filesystem.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// File Info
// - Immutable
//

class FileInfo
{
public:

    explicit FileInfo( const Path& path );

    Bool Exists() const;


protected:

    // NOTES: m_status depends on m_path,
    //        therefore m_path must be in front of m_status.

    Path m_path;
    boost::filesystem::file_status m_status;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementations
//

inline FileInfo::FileInfo( const Path& path )
    : m_path( path )
    , m_status( boost::filesystem::status( path ))
{
}


inline Bool FileInfo::Exists() const
{
    return boost::filesystem::is_regular_file( m_status )
        && boost::filesystem::exists( m_status );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_SYSTEM_FILE_INFO_H
