// Caramel C++ Library - File System Amenity - Path Header

#ifndef __CARAMEL_FILE_SYSTEM_PATH_H
#define __CARAMEL_FILE_SYSTEM_PATH_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/String/Utf8String.h>
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

    explicit Path( const Utf8String& u8path );

    
    //
    // Native format properties
    //
    //   Different |  directory       |  string_type
    //             |  separators      |
    //  ---------------------------------------------
    //   Windows   |  back-slash '\'  |  wstring
    //   Other OS  |  slash '/'       |  string
    //

    Utf8String Stem()      const { return Utf8String( this->stem().native() ); }
    Utf8String Extension() const { return Utf8String( this->extension().native() ); }


    //
    // Conversion
    // - Path always can be converted to UTF-8 string.
    //

    operator Utf8String() const { return Utf8String( this->native() ); }

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementations
//

#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

//
// For Windows, path's value_type is wchar_t.
// If you don't give codecvt, it would think the input string as ACP (active code page).
//
inline Path::Path( const Utf8String& path )
    : boost::filesystem::path( path.ToWstring() )
{
}


#else

inline Path::Path( const Utf8String& path )
    : boost::filesystem::path( path )
{
}


#endif  // CARAMEL_SYSTEM_IS_WINDOWS


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_SYSTEM_PATH_H
