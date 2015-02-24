// Caramel C++ Library - Document Facility - INI Section Private Header

#ifndef __CARAMEL_DOCUMENT_INI_SECTION_IMPL_H
#define __CARAMEL_DOCUMENT_INI_SECTION_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Document/IniSection.h>
#include <Caramel/String/CainLess.h>
#include <Caramel/Value/Scalar.h>
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
    friend class IniDocumentImpl;
    friend class IniSection;

public:
    
    IniSectionImpl( const std::string& name, const std::string& rawLine );


    /// Properties ///

    std::string GetName() const { return m_name; }


    /// Value Accessors ///

    Bool HasValue( const std::string& valueName ) const;

    Scalar GetValue( const std::string& valueName ) const;


    /// Value Manipulators ///

    void AddValue(
        const std::string& valueName, 
        const std::string& value,
        const std::string& rawline
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
        Scalar      value;
        std::size_t rawLineIndex { 0 };
    };

    typedef std::map< std::string, ValueEntry, CainLess > ValueMap;
    ValueMap m_values;


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

#endif // __CARAMEL_DOCUMENT_INI_SECTION_IMPL_H
