// Caramel C++ Library - File View Facility - INI File Syntax Header

#ifndef __CARAMEL_FILE_VIEW_INI_SYNTAX_H
#define __CARAMEL_FILE_VIEW_INI_SYNTAX_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Io/TextReader.h>
#include <Caramel/String/Utf8String.h>
#include <vector>


namespace Caramel
{

//
// INI Syntax
//
// There are two components here:
// - INI Line
// - INI Array
//

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
        TYPE_ARRAY_BEGIN,
        TYPE_INVALID,
    };

    explicit IniLine( const Utf8String& rawLine );

    
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
//
// INI Array
//

class IniArray
{
public:
    
    explicit IniArray( const Utf8String& firstRawLine );

    Bool TryRead( TextReader& reader, Uint& lineNo );


    /// Properties ///

    std::vector< Utf8String > Values()   const { return m_values; }
    std::vector< Utf8String > RawLines() const { return m_rawLines; }


private:

    Bool ParseLine( const Utf8String& rawLine, Uint& lineNo );


    /// Data Members ///

    Utf8String m_firstRawLine;

    Bool m_failed;

    std::vector< Utf8String > m_values;
    std::vector< Utf8String > m_rawLines;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_VIEW_INI_SYNTAX_H
