// Caramel C++ Library - File System Facility - Path Header

#ifndef __CARAMEL_FILE_SYSTEM_PATH_H
#define __CARAMEL_FILE_SYSTEM_PATH_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/String/StringConvertible.h>
#include <Caramel/String/Utf8String.h>
#include <boost/operators.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Path
// - Based on Boost.Filesystem library
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
           , public boost::dividable< Path >
{
    friend class DirectoryInfo;
    friend class FileInfo;

public:

    Path();
    
    Path( const Utf8String& u8path );

    //
    // Throws if the path is not UTF-8 encoded.
    //
    Path( const std::string& path );
    Path( const Char* path );
    
    template< typename T >
    Path( const StringConvertible< T >& path );


    //
    // Splits
    //

    Path Directory() const;
    Path Stem()      const;
    Path Extension() const;


    //
    // Predicates
    //

    Bool HasExtension() const;
    Bool IsAbsolute()   const;


    //
    // Combine two path with native separator.
    // - Add separator between two paths if the first path doesn't end with a separator.
    //
    void Combine( const Path& subpath );

    Path& operator/=( const Path& subpath );


    //
    // Manipulators
    //

    //
    // Whether or not the extension has a prefix '.', the result is append with just one '.'
    // EXAMPLE:
    //   ReadMe + .txt => ReadMe.txt
    //   ReadMe + txt  => ReadMe.txt
    //
    void AppendExtension( const std::string& extension );

    //
    // Insert a suffix after the stem, that is, before the last '.' character.
    // EXAMPLE
    //   MyLog.txt     + _0815 => MyLog_0815.txt
    //   MyLog.bak.txt + _0815 => MyLog.bak_0815.txt
    //
    void InsertStemSuffix( const std::string& suffix );


    //
    // Conversion
    // - Returns in UTF-8 string.
    //

    operator std::string() const;
    std::string ToString() const;

    Utf8String ToUtf8String() const;


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

    explicit Path( std::shared_ptr< PathImpl > impl );

    void Init( const std::string& path );

    std::shared_ptr< PathImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T >
Path::Path( const StringConvertible< T >& path )
{
    this->Init( static_cast< const T& >( path ).ToString() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_SYSTEM_PATH_H
