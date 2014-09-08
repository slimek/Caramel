// Caramel C++ Library - Document Facility - INI Section Header

#ifndef __CARAMEL_FILE_VIEW_INI_SECTION_H
#define __CARAMEL_FILE_VIEW_INI_SECTION_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <vector>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// INI Section
//

class IniSectionImpl;

class IniSection
{
    friend class IniDocument;

public:

    /// Value Accessors ///

    Bool HasValue( const std::string& valueName ) const;


    //
    // Get Values 
    // - These functions throw exceptions if ...
    //   1. The value doesn't exist.
    //   2. The value can't be converted to the type.
    //

    Bool   GetBool ( const std::string& valueName ) const;
    Int    GetInt  ( const std::string& valueName ) const;
    Uint   GetUint ( const std::string& valueName ) const;
    Float  GetFloat( const std::string& valueName ) const;

    //
    // Get String Value
    // - If the value is quoted, the beginning and ending quotes would be removed.
    //   The string is UTF-8 encoded.
    //    
    std::string GetString( const std::string& valueName ) const;


    //
    // Get Array Values
    //
    //std::vector< std::string > GetStringArray( const std::string& valueName ) const;


private:

    explicit IniSection( std::shared_ptr< IniSectionImpl > impl );

    std::shared_ptr< IniSectionImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_VIEW_INI_SECTION_H
