// Caramel C++ Library - File View Facility - INI File View Header

#ifndef __CARAMEL_FILE_VIEW_INI_FILE_VIEW_H
#define __CARAMEL_FILE_VIEW_INI_FILE_VIEW_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/FileSystem/Path.h>
#include <Caramel/FileView/IniSection.h>
#include <Caramel/Io/TextReader.h>
#include <Caramel/String/Utf8String.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// INI File View
//

class IniFileViewImpl;

class IniFileView
{
public:

    IniFileView();
    explicit IniFileView( const Utf8String& fileName );

    ~IniFileView();


    //
    // Storage Operations
    //

    void LoadFromFile( const Utf8String& fileName );
    void LoadFromText( TextReader& reader );

    void SaveToFile( const Utf8String& fileName, TextEncoding encoding );

    //
    // Save to file with the encoding when the view is loaded.
    // If no file was loaded, the encoding would be UTF-8 with BOM.
    //
    void SaveToFile( const Utf8String& fileName );


    //
    // Section Manipulations
    // - Section name should be ASCII string.
    //

    Bool HasSection( const std::string& sectionName );

    const IniSection* GetSection( const std::string& sectionName ) const;
    IniSection*       GetSection( const std::string& sectionName );


private:

    //
    // Data Members
    //

    std::unique_ptr< IniFileViewImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_VIEW_INI_FILE_VIEW_H

