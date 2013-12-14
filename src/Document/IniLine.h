// Caramel C++ Library - Document Facility - INI Line Header

#ifndef __CARAMEL_DOCUMENT_INI_LINE_H
#define __CARAMEL_DOCUMENT_INI_LINE_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Io/TextReader.h>
#include <vector>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// INI Line
//

class IniLine
{
public:

    enum TypeValue
    {
        TYPE_UNDEF,
        TYPE_BLANK,    // Empty lines or comments
        TYPE_SECTION,
        TYPE_VALUE,
        TYPE_INVALID,
    };

    explicit IniLine( const std::string& rawLine );

    
    /// Properties ///

    TypeValue Type() const { return m_type; }

    std::string Name()  const { return m_name; }
    std::string Value() const { return m_value; }


private:

    void Parse();


    /// Data Members ///

    std::string m_rawLine;

    TypeValue   m_type;

    std::string m_name;
    std::string m_value;
    Int         m_valueBegin;
    Bool        m_quoted;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DOCUMENT_INI_LINE_H
