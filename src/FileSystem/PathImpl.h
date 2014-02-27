// Caramel C++ Library - File System Facility - Path Private Header

#ifndef __CARAMEL_FILE_SYSTEM_PATH_IMPL_H
#define __CARAMEL_FILE_SYSTEM_PATH_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/FileSystem/Path.h>
#include <boost/filesystem.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Path
//

class PathImpl : public boost::filesystem::path
{
public:

    explicit PathImpl( const boost::filesystem::path& path );
    explicit PathImpl( boost::filesystem::path&& path );
    explicit PathImpl( const Utf8String& path );
    
    // Returns a UTF-8 string
    Utf8String  ToUtf8String() const;
    std::string ToString()     const;

};

typedef std::shared_ptr< PathImpl > PathPtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_SYSTEM_PATH_IMPL_H
