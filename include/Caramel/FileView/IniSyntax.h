// Caramel C++ Library - File View Facility - INI File Syntax Header

#ifndef __CARAMEL_FILE_VIEW_INI_SYNTAX_H
#define __CARAMEL_FILE_VIEW_INI_SYNTAX_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/String/Utf8String.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// INI Syntax
//

class IniSyntax
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

    explicit IniSyntax( const Utf8String& rawLine );

    
    /// Properties ///

    TypeValue Type() const { return m_type; }

    std::string Name()  const { return m_name; }
    Utf8String  Value() const { return m_value; }


private:

    void Parse();


    /// Data Members ///

    Utf8String m_rawLine;

    TypeValue m_type;

    std::string m_name;
    Utf8String  m_value;
    Int         m_valueBegin;
    Bool        m_quoted;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_VIEW_INI_SYNTAX_H
