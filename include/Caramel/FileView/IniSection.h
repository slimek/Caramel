// Caramel C++ Library - File View Amenity - INI Section Header

#ifndef __CARAMEL_FILE_VIEW_INI_SECTION_H
#define __CARAMEL_FILE_VIEW_INI_SECTION_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/String/Utf8String.h>
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
    friend class IniFileView;

public:

    /// Value Accessors ///

    Bool HasValue( const std::string& valueName ) const;


    //
    // Get Values 
    // - These functions throw exceptions if ...
    //   1. The value doesn't exist.
    //   2. The value can't be converted to the type.
    //

    Bool   GetBoolValue ( const std::string& valueName ) const;
    Int    GetIntValue  ( const std::string& valueName ) const;
    Uint   GetUintValue ( const std::string& valueName ) const;
    Float  GetFloatValue( const std::string& valueName ) const;

    //
    // Get String Value
    // - If the value is quoted, the beginning and ending quotes would be removed.
    //    
    Utf8String GetStringValue( const std::string& valueName ) const;


    //
    // Get Array Values
    //

    std::vector< Utf8String > GetStringArrayValue( const std::string& valueName ) const;


private:

    explicit IniSection( std::shared_ptr< IniSectionImpl > impl );

    std::shared_ptr< IniSectionImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_VIEW_INI_SECTION_H
