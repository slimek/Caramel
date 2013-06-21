// Caramel C++ Library - File System Amenity - Path Header

#ifndef __CARAMEL_FILE_SYSTEM_PATH_H
#define __CARAMEL_FILE_SYSTEM_PATH_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <boost/filesystem.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Path
// - Immutable
//

class Path : public boost::filesystem::path
{

public:
    explicit Path( const std::string& path );

    
    //
    // Native format properties
    // - Major different is the directory separators.
    //   In Windows it is back-slash '\'
    //   In other OS it is slash '/'
    //

    std::string Stem()      const { return this->stem().string(); }
    std::string Extension() const { return this->extension().string(); }

};


//
// Implementations
//

inline Path::Path( const std::string& path )
    : boost::filesystem::path( path )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_SYSTEM_PATH_H
