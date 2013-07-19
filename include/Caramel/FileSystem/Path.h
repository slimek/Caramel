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
//   Used as function parameters in other FileSystem classes,
//   Therefore it provides both std::string and const Char* constructors.
//
//   Different |  directory       |  value_type  |  string_type
//             |  separators      |              |
//  ------------------------------------------------------------
//   Windows   |  back-slash '\'  |  wchar_t     |  wstring
//   Other OS  |  slash '/'       |  char        |  string
//

class Path : public boost::filesystem::path
{
public:

    Path();
    Path( const boost::filesystem::path& path );

    Path( const Utf8String& u8path );

    //
    // Construct from OS default encoding
    //

    Path( const std::string& path );
    Path( const Char* path );
    

    //
    // Splits
    //

    Path Stem()      const { return Path( this->stem() ); }
    Path Extension() const { return Path( this->extension() ); }


    //
    // Predicates
    //

    Bool HasExtension() const { return this->has_extension(); }


    //
    // Compositions
    // - Don't change this object, return the result as a copy.
    //

    //
    // Append Extension
    // - Whether or not the extension has a prefix '.', the result is append with just one '.'
    //
    Path AppendExtension( const std::string& extension ) const;


    //
    // Conversion
    // - Path always can be converted to UTF-8 string.
    //

    operator Utf8String() const { return Utf8String( this->native() ); }


    //
    // Member Types
    //

    typedef boost::filesystem::path::value_type ValueType;
    typedef CharTraits< ValueType > TraitsType;


#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

    //
    // Construct from wide string
    //

    Path( const std::wstring& wpath );
    Path( const Wchar* wpath );

#endif // CARAMEL_SYSTEM_IS_WINDOWS

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementations
//

inline Path::Path()
{
}


inline Path::Path( const boost::filesystem::path& path )
    : boost::filesystem::path( path )
{
}


//
// Construct from OS default encoding.
// - In Windows, it is ACP (acitve code page).
//   In other OS, it is UTF-8.
//

inline Path::Path( const std::string& path )
    : boost::filesystem::path( path )
{
}


inline Path::Path( const Char* path )
    : boost::filesystem::path( path )
{
}


#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

//
// For Windows, path's value_type is wchar_t.
// If you don't give codecvt, it would think the input string as ACP (active code page).
//
inline Path::Path( const Utf8String& path )
    : boost::filesystem::path( path.ToWstring() )
{
}


inline Path::Path( const std::wstring& wpath )
    : boost::filesystem::path( wpath )
{
}


inline Path::Path( const Wchar* wpath )
    : boost::filesystem::path( wpath )
{
}

#else

inline Path::Path( const Utf8String& path )
    : boost::filesystem::path( path )
{
}

#endif  // CARAMEL_SYSTEM_IS_WINDOWS


//
// Compositions
//

inline Path Path::AppendExtension( const std::string& extension ) const
{
    if ( extension.empty() ) { return *this; }

    const Utf8String u8Path( *this );
    const Utf8String u8Dot( '.' );
    const Utf8String u8Ext( extension );

    return Path( '.' == extension[0] ? u8Path + u8Ext
                                     : u8Path + u8Dot + u8Ext );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_SYSTEM_PATH_H
