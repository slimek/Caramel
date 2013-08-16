// Caramel C++ Library - File View Facility - INI File View Private Header

#ifndef __CARAMEL_FILE_VIEW_INI_FILE_VIEW_IMPL_H
#define __CARAMEL_FILE_VIEW_INI_FILE_VIEW_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/FileView/IniFileView.h>
#include <Caramel/String/CainLess.h>
#include <map>


namespace Caramel
{

class IniSectionImpl;
typedef std::shared_ptr< IniSectionImpl > IniSectionPtr;

///////////////////////////////////////////////////////////////////////////////
//
// INI File View
//

class IniFileViewImpl
{
    friend class IniFileView;

public:

    IniFileViewImpl();

    void LoadFromText( TextReader& reader );


    /// Section Management ///

    void AddSection( const std::string& sectionName, const std::string& rawLine );

    IniSectionPtr FindSection( const std::string& sectionName ) const;


private:

    /// Manipulators ///

    void Clear();


    /// Data Members ///

    TextEncoding m_textEncoding;

    IniSectionPtr m_currSection;

    typedef std::map< std::string, IniSectionPtr, CainLess > SectionMap;
    SectionMap m_sectionMap;

    typedef std::vector< IniSectionPtr > SectionSeq;
    SectionSeq m_sectionSeq;  // Keep the order of sections in the INI file.

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_FILE_VIEW_INI_FILE_VIEW_IMPL_H
