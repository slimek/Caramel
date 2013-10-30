// Caramel C++ Library - Document Facility - INI Document Private Header

#ifndef __CARAMEL_DOCUMENT_INI_DOCUMENT_IMPL_H
#define __CARAMEL_DOCUMENT_INI_DOCUMENT_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Document/IniDocument.h>
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

class IniDocumentImpl
{
    friend class IniFileView;

public:

    IniDocumentImpl();

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

#endif // __CARAMEL_DOCUMENT_INI_DOCUMENT_IMPL_H
