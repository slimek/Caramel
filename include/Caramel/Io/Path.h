// Caramel C++ Library - I/O Amenity - Path Header

#ifndef __CARAMEL_IO_PATH_H
#define __CARAMEL_IO_PATH_H

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

class Path
{

public:
    explicit Path( const std::string& path );

    
    //
    // Native format properties
    // - Major different is the directory separators.
    //   In Windows it is back-slash '\'
    //   In other OS it is slash '/'
    //

    std::string Stem()      const { return m_path.stem().string(); }
    std::string Extension() const { return m_path.extension().string(); }


private:

    boost::filesystem::path m_path;
};


//
// Implementations
//

inline Path::Path( const std::string& path )
    : m_path( path )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_IO_PATH_H
