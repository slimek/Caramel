// Caramel C++ Library - File View Amenity - INI Section Private Header

#ifndef __CARAMEL_FILE_VIEW_INI_SECTION_IMPL_H
#define __CARAMEL_FILE_VIEW_INI_SECTION_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/FileView/IniSection.h>
#include <Caramel/String/CainLess.h>
#include <deque>
#include <map>
#include <vector>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// INI Section
//

class IniSectionImpl
{
    friend class IniFileViewImpl;

public:
    
    IniSectionImpl( const std::string& name, const Utf8String& rawLine );


    /// Properties ///

    std::string GetName() const { return m_name; }


    /// Value Accessors ///

    Bool HasValue( const std::string& valueName ) const;

    Utf8String GetStringValue( const std::string& valueName ) const;

    std::vector< Utf8String > GetStringArrayValue( const std::string& valueName ) const;


    /// Value Manipulators ///

    void AddValue(
        const std::string& valueName, 
        const Utf8String&  value,
        const Utf8String&  rawline
    );

    void AddArrayValue(
        const std::string& valueName,
        const std::vector< Utf8String >& values,
        const std::vector< Utf8String >& rawLines
    );



private:

    //
    // Manipulations
    //

    void AddRawLine( const Utf8String& rawLine );


    //
    // Data Members
    //

    std::string m_name;  // section name

    struct ValueEntry
    {
        ValueEntry()
            : rawLineIndex( 0 )
        {}

        Utf8String value;
        Uint       rawLineIndex;
    };

    typedef std::map< std::string, ValueEntry, CainLess > ValueMap;
    ValueMap m_values;


    struct ArrayValueEntry
    {
        ArrayValueEntry()
            : lastRawLineIndex( 0 )
        {}

        std::vector< Utf8String > values;
        Uint lastRawLineIndex;
    };

    typedef std::map< std::string, ArrayValueEntry, CainLess > ArrayValueMap;
    ArrayValueMap m_arrayValues;


    struct RawLineEntry
    {
        Utf8String  rawLine;
        std::string valueName;
    };

    typedef std::deque< RawLineEntry > RawLineSequence;
    RawLineSequence m_rawLines;
};

typedef std::shared_ptr< IniSectionImpl > IniSectionPtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_VIEW_INI_SECTION_IMPL_H
