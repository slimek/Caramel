// Caramel C++ Library - File System Facility - Path Header

#ifndef __CARAMEL_FILE_SYSTEM_PATH_H
#define __CARAMEL_FILE_SYSTEM_PATH_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/String/StringConvertible.h>
#include <Caramel/String/Utf8String.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Path
// - Immutable
//   Based on Boost.Filesystem library
//
//   Used as function parameters in other FileSystem classes,
//   Therefore it provides both std::string and const Char* constructors.
//
//   Different |  directory       |  value_type  |  string_type
//             |  separators      |              |
//  ------------------------------------------------------------
//   Windows   |  back-slash '\'  |  wchar_t     |  wstring
//   Other OS  |  slash '/'       |  char        |  string
//
//

class PathImpl;

class Path : public StringConvertible< Path >
{
public:

    Path();
    
    Path( const Utf8String& u8path );

    //
    // Construct from OS default encoding
    //

    Path( const std::string& path );
    Path( const Char* path );


    //
    // Splits
    //

    Path Stem()      const;
    Path Extension() const;


    //
    // Predicates
    //

    Bool HasExtension() const;


    //
    // Compositions
    // - Don't change this object, return the result as a copy.
    //

    //
    // Combine
    // - Add separator between two paths if the first path doesn't end with a separator.
    //
    Path Combine( const Path& subpath ) const;

    //
    // Append Extension
    // - Whether or not the extension has a prefix '.', the result is append with just one '.'
    //
    Path AppendExtension( const std::string& extension ) const;


    //
    // Conversion
    // - Path always can be converted to UTF-8 string.
    //

    operator   Utf8String()   const;
    Utf8String ToUtf8String() const;

    std::string ToString()    const;


#if defined( CARAMEL_SYSTEM_IS_WINDOWS )

    //
    // Construct from wide string
    //

    Path( const std::wstring& wpath );
    Path( const Wchar* wpath );


    //
    // Conversion to wide string
    //

    std::wstring ToWstring() const;


#endif // CARAMEL_SYSTEM_IS_WINDOWS


private:

    explicit Path( PathImpl* impl );

    std::shared_ptr< PathImpl > m_impl;

    friend class FileInfo;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_SYSTEM_PATH_H
