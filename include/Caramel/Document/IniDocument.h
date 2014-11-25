// Caramel C++ Library - Document Facility - INI Document Header

#ifndef __CARAMEL_DOCUMENT_INI_DOCUMENT_H
#define __CARAMEL_DOCUMENT_INI_DOCUMENT_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Document/IniSection.h>
#include <Caramel/FileSystem/Path.h>
#include <Caramel/Io/TextReader.h>
#include <Caramel/String/Utf8String.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// INI Document
//

class IniDocumentImpl;

class IniDocument
{
public:

    IniDocument();

    explicit IniDocument( const std::string& fileName );
    explicit IniDocument( const Utf8String&  fileName );

    ~IniDocument();


    //
    // Storage Operations
    //

    void LoadFromFile( const std::string& fileName );
    void LoadFromFile( const Utf8String&  fileName );

    void LoadFromText( TextReader& reader );
    void LoadFromText( TextReader&& reader );

    void SaveToFile( const std::string& fileName, TextEncoding encoding );
    void SaveToFile( const Utf8String&  fileName, TextEncoding encoding );

    //
    // Save to file with the encoding when the view is loaded.
    // If no file was loaded, the encoding would be UTF-8 with BOM.
    //
    void SaveToFile( const std::string& fileName );
    void SaveToFile( const Utf8String&  fileName );


    //
    // Section Manipulations
    // - Section name should be ASCII string.
    //

    Bool HasSection( const std::string& sectionName );

    IniSection GetSection( const std::string& sectionName );

    std::vector< IniSection > GetAllSections() const;


private:

    //
    // Data Members
    //

    std::unique_ptr< IniDocumentImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DOCUMENT_INI_DOCUMENT_H

