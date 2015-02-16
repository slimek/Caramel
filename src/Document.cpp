// Caramel C++ Library - Document Facility - Implementation

#include "CaramelPch.h"

#include "Document/IniDocumentImpl.h"
#include "Document/IniLine.h"
#include "Document/IniSectionImpl.h"
#include <Caramel/Io/InputFileStream.h>
#include <Caramel/Io/TextStreamReader.h>
#include <Caramel/Lexical/Boolean.h>
#include <Caramel/Lexical/Integer.h>
#include <Caramel/String/Algorithm.h>
#include <boost/xpressive/xpressive_dynamic.hpp>


namespace Caramel
{

//
// Contents
//
//   IniDocument
//   IniSection
//   IniLine
//

///////////////////////////////////////////////////////////////////////////////
//
// INI Document
//

IniDocument::IniDocument()
    : m_impl( new IniDocumentImpl )
{
}


IniDocument::IniDocument( const std::string& fileName )
    : m_impl( new IniDocumentImpl )
{
    CARAMEL_CHECK_UTF8_ARGUMENT( u8FileName, fileName );

    this->LoadFromFile( u8FileName );
}


IniDocument::IniDocument( const Utf8String& fileName )
    : m_impl( new IniDocumentImpl )
{
    this->LoadFromFile( fileName );
}


IniDocument::~IniDocument()
{
}


void IniDocument::LoadFromFile( const std::string& fileName )
{
    CARAMEL_CHECK_UTF8_ARGUMENT( u8FileName, fileName );

    this->LoadFromFile( u8FileName );
}


void IniDocument::LoadFromFile( const Utf8String& fileName )
{
    Path path( fileName );
    
    if ( ! path.HasExtension() )
    {
        path.AppendExtension( "ini" );
    }

    InputFileStream file( path );
    TextStreamReader reader( file );

    m_impl->LoadFromText( reader );
}


void IniDocument::LoadFromText( TextReader& reader )
{
    m_impl->LoadFromText( reader );
}


void IniDocument::LoadFromText( TextReader&& reader )
{
    m_impl->LoadFromText( reader );
}


IniSection IniDocument::GetSection( const std::string& sectionName )
{
    IniSectionPtr section = m_impl->FindSection( sectionName );
    if ( ! section )
    {
        CARAMEL_THROW( "Section \"{0}\" not found", sectionName );
    }

    return IniSection( section );
}


std::vector< IniSection > IniDocument::GetAllSections() const
{
    const auto& sects = m_impl->m_sectionMap;

    std::vector< IniSection > result;
    result.reserve( sects.size() );

    for ( const auto& sect : sects )
    {
        result.push_back( IniSection( sect.second ));
    }

    return result;
}


//
// Implementation
//

IniDocumentImpl::IniDocumentImpl()
    : m_textEncoding( TEXT_ENCODING_UTF8 )
    , m_currSection( nullptr )
{
}


void IniDocumentImpl::LoadFromText( TextReader& reader )
{
    this->Clear();

    Uint lineNo = 0;
    std::string rawLine;
    while ( reader.ReadLine( rawLine ))
    {
        ++ lineNo;

        IniLine iniLine( rawLine );

        switch ( iniLine.Type() )
        {
        case IniLine::TYPE_SECTION:
            this->AddSection( iniLine.Name(), rawLine );
            break;

        case IniLine::TYPE_BLANK:
            if ( m_currSection )
            {
                m_currSection->AddRawLine( rawLine );
            }
            break;

        case IniLine::TYPE_VALUE:
            if ( ! m_currSection )
            {
                CARAMEL_THROW( "No section given before the first value: \"{0}\"", iniLine.Name() );
            }
            m_currSection->AddValue( iniLine.Name(), iniLine.Value(), rawLine );
            break;

        case IniLine::TYPE_INVALID:
            CARAMEL_THROW( "Line: {0} : Syntax error in section \"{1}\"",
                           lineNo, m_currSection->GetName() );

        default:
            CARAMEL_NOT_REACHED();
        }
    }
}


//
// Manipulators
//

void IniDocumentImpl::Clear()
{
    m_currSection.reset();
    m_sectionMap.clear();
    m_sectionSeq.clear();
}


//
// Section Management
//

void IniDocumentImpl::AddSection( const std::string& sectionName, const std::string& rawLine )
{
    SectionMap::iterator is = m_sectionMap.find( sectionName );
    if ( m_sectionMap.end() != is )
    {
        CARAMEL_THROW( "Section duplicate, name: \"{0}\"", sectionName );
    }

    m_currSection.reset( new IniSectionImpl( sectionName, rawLine ));

    m_sectionMap.insert( std::make_pair( sectionName, m_currSection ));

    m_sectionSeq.push_back( m_currSection );
}


IniSectionPtr IniDocumentImpl::FindSection( const std::string& sectionName ) const
{
    SectionMap::const_iterator is = m_sectionMap.find( sectionName );
    if ( m_sectionMap.end() == is )
    {
        return IniSectionPtr();
    }
    return is->second;
}


///////////////////////////////////////////////////////////////////////////////
//
// INI Section
//

IniSection::IniSection( IniSectionPtr impl )
    : m_impl( impl )
{
}


std::string IniSection::GetName() const
{
    return m_impl->GetName();
}


//
// Value Accessors
//

Bool IniSection::HasValue( const std::string& valueName ) const
{
    return m_impl->HasValue( valueName );
}


Bool IniSection::GetBool( const std::string& valueName ) const
{
    const auto value = m_impl->GetValue( valueName );
    const auto bvalue = value.AsBool();
    if ( ! bvalue )
    {
        CARAMEL_THROW( "Can't convert value {0} \"{1}\" to Bool, in section \"{2}\"",
                       valueName, value, m_impl->GetName() );
    }
    return *bvalue;
}


Int IniSection::GetInt( const std::string& valueName ) const
{
    const auto value = m_impl->GetValue( valueName );
    const auto ivalue = value.AsInt();
    if ( ! ivalue )
    {
        CARAMEL_THROW( "Can't convert value {0} \"{1}\" to Int, in section \"{2}\"",
                       valueName, value, m_impl->GetName() );
    }
    return *ivalue;
}


Uint IniSection::GetUint( const std::string& valueName ) const
{
    const auto value = m_impl->GetValue( valueName );
    const auto uvalue = value.AsUint();
    if ( ! uvalue )
    {
        CARAMEL_THROW( "Can't convert value {0} \"{1}\" to Uint, in section \"{2}\"",
                       valueName, value, m_impl->GetName() );
    }
    return *uvalue;
}


Float IniSection::GetFloat( const std::string& valueName ) const
{
    const auto value = m_impl->GetValue( valueName );
    const auto fvalue = value.AsFloat();
    if ( ! fvalue )
    {
        CARAMEL_THROW( "Can't convert value {0} \"{1}\" to Float, in section \"{2}\"",
                       valueName, value, m_impl->GetName() );
    }
    return *fvalue;
}


std::string IniSection::GetString( const std::string& valueName ) const
{
    return *( m_impl->GetValue( valueName ).AsString() );
}


NamedValues IniSection::ToNamedValues() const
{
    const auto& values = m_impl->m_values;

    NamedValues result;
    for ( const auto& nameValue : values )
    {
        result[ nameValue.first ] = nameValue.second.value;
    }

    return result;
}


//
// Implementation
//

IniSectionImpl::IniSectionImpl( const std::string& name, const std::string& rawLine )
    : m_name( name )
{
    if ( ! rawLine.empty() )
    {
        this->AddRawLine( rawLine );
    }
}


//
// Value Accessors
//

Bool IniSectionImpl::HasValue( const std::string& valueName ) const
{
    return m_values.end() != m_values.find( valueName );
}


Scalar IniSectionImpl::GetValue( const std::string& valueName ) const
{
    auto ivalue = m_values.find( valueName );
    if ( ivalue != m_values.end() )
    {
        return ivalue->second.value;
    }

    CARAMEL_THROW( "Value \"{0}\" not found in section \"{1}\"", valueName, m_name );
}


//
// Manipulations
//

void IniSectionImpl::AddValue(
    const std::string& valueName, const std::string& inputValue, const std::string& inputRawLine )
{
    if ( this->HasValue( valueName ))
    {
        CARAMEL_THROW( "Duplicate value \"{0}\" in section \"{1}\"", valueName, m_name );
    }

    ValueEntry value;
    value.value = Scalar( inputValue );
    value.rawLineIndex = m_rawLines.size();

    m_values.insert( std::make_pair( valueName, value ));

    RawLineEntry rawLine;
    rawLine.rawLine = inputRawLine;
    rawLine.valueName = valueName;

    m_rawLines.push_back( rawLine );
}


void IniSectionImpl::AddRawLine( const std::string& inputRawLine )
{
    RawLineEntry rawLine;
    rawLine.rawLine = inputRawLine;

    m_rawLines.push_back( rawLine );
}


///////////////////////////////////////////////////////////////////////////////
//
// INI Line
//

static std::string RemoveCommentsAndTrim( const std::string& rawLine )
{
    Usize pos = 0;
    Bool quoted = false;
    while ( pos < rawLine.length() )
    {
        const Char c = rawLine[ pos ];
        if (( ';' == c || '#' == c ) && ! quoted )
        {
            // After the char are comments.
            break;
        }
        else if ( '"' == c )
        {
            quoted = ! quoted;
        }

        ++ pos;
    }

    std::string line = rawLine.substr( 0, pos );
    Trim( line );

    return line;
}


IniLine::IniLine( const std::string& rawLine )
    : m_rawLine( rawLine )
    , m_type( TYPE_UNDEF )
    , m_valueBegin( -1 )
    , m_quoted( false )
{
    this->Parse();
}


void IniLine::Parse()
{
    const std::string line = RemoveCommentsAndTrim( m_rawLine );
    
    if ( line.empty() )
    {
        m_type = TYPE_BLANK;
        return;
    }

    using namespace boost::xpressive;

    smatch matches;
    const sregex section     = sregex::compile( "\\[(.*)\\]" );
    const sregex quotedValue = sregex::compile( "([^=\\s]*)\\s*=\\s*\"([^\"]*)\"" );
    const sregex value       = sregex::compile( "([^=\\s]*)\\s*=\\s*([^\\s]*)" );

    if ( regex_match( line, matches, section ))
    {
        m_type = TYPE_SECTION;
        m_name = matches[1];
    }
    else if ( regex_match( line, matches, quotedValue ))
    {
        // REMARKS: You must match 'quotedValue' before 'value'.

        m_type = TYPE_VALUE;
        m_name = matches[1];
        m_value = matches[2];
        m_valueBegin = matches.position( 2 );
        m_quoted = true;
    }
    else if ( regex_match( line, matches, value ))
    {
        m_type = TYPE_VALUE;
        m_name = matches[1];
        m_value = matches[2];
        m_valueBegin = matches.position( 2 );
    }
    else
    {
        m_type = TYPE_INVALID;
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
