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
    
    IniSectionImpl( const std::string& name, const std::string& rawLine );


    /// Properties ///

    std::string GetName() const { return m_name; }


    /// Value Accessors ///

    Bool HasValue( const std::string& valueName ) const;

    std::string GetStringValue( const std::string& valueName ) const;

    std::vector< std::string > GetStringArrayValue( const std::string& valueName ) const;


    /// Value Manipulators ///

    void AddValue(
        const std::string& valueName, 
        const std::string& value,
        const std::string& rawline
    );

    void AddArrayValue(
        const std::string& valueName,
        const std::vector< std::string >& values,
        const std::vector< std::string >& rawLines
    );



private:

    //
    // Manipulations
    //

    void AddRawLine( const std::string& rawLine );


    //
    // Data Members
    //

    std::string m_name;  // section name

    struct ValueEntry
    {
        ValueEntry()
            : rawLineIndex( 0 )
        {}

        std::string value;
        Uint        rawLineIndex;
    };

    typedef std::map< std::string, ValueEntry, CainLess > ValueMap;
    ValueMap m_values;


    struct ArrayValueEntry
    {
        ArrayValueEntry()
            : lastRawLineIndex( 0 )
        {}

        std::vector< std::string > values;
        Uint lastRawLineIndex;
    };

    typedef std::map< std::string, ArrayValueEntry, CainLess > ArrayValueMap;
    ArrayValueMap m_arrayValues;


    struct RawLineEntry
    {
        std::string rawLine;
        std::string valueName;
    };

    typedef std::deque< RawLineEntry > RawLineSequence;
    RawLineSequence m_rawLines;
};

typedef std::shared_ptr< IniSectionImpl > IniSectionPtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_VIEW_INI_SECTION_IMPL_H
