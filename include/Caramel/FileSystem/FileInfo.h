// Caramel C++ Library - File System Amenity - File Info Header

#ifndef __CARAMEL_FILE_SYSTEM_FILE_INFO_H
#define __CARAMEL_FILE_SYSTEM_FILE_INFO_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

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

    explicit FileInfo( const std::string& fileName );

    Bool Exists() const;


private:

    std::string m_fileName;
    boost::filesystem::file_status m_status;
};


//
// Implementations
//

inline FileInfo::FileInfo( const std::string& fileName )
    : m_fileName( fileName )
    , m_status( boost::filesystem::status( fileName ))
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
