// Caramel C++ Library - Document Facility - Implementation

#include "CaramelPch.h"

#include "Document/IniDocumentImpl.h"
#include "Document/IniSectionImpl.h"
#include "Document/IniSyntax.h"
#include <Caramel/Io/InputFileStream.h>
#include <Caramel/Io/TextStreamReader.h>
#include <Caramel/Lexical/Boolean.h>
#include <Caramel/Lexical/Integer.h>
#include <Caramel/String/Algorithm.h>
#include <boost/tokenizer.hpp>
#include <regex>


namespace Caramel
{

//
// Contents
//
//   IniDocument
//   IniSection
//   IniLine
//   IniArray
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


IniSection IniDocument::GetSection( const std::string& sectionName )
{
    IniSectionPtr section = m_impl->FindSection( sectionName );
    if ( ! section )
    {
        CARAMEL_THROW( "Section %s not found", sectionName );
    }

    return IniSection( section );
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
    this->AddSection( "", "" );

    Uint lineNo = 0;
    std::string rawLine;
    while ( reader.ReadLine( rawLine ))
    {
        ++ lineNo;

        IniLine iniLine( rawLine );

        switch ( iniLine.Type() )
        {
        case IniLine::TYPE_BLANK:
            m_currSection->AddRawLine( rawLine );
            break;

        case IniLine::TYPE_SECTION:
            this->AddSection( iniLine.Name(), rawLine );
            break;

        case IniLine::TYPE_VALUE:
            m_currSection->AddValue( iniLine.Name(), iniLine.Value(), rawLine );
            break;

        case IniLine::TYPE_ARRAY_BEGIN:
        {
            IniArray iniArray( rawLine );
            if ( ! iniArray.TryRead( reader, lineNo ))
            {
                CARAMEL_THROW( "Array value %s syntax error in %s section",
                               iniLine.Name(), m_currSection->GetName() );
            }

            m_currSection->AddArrayValue( iniLine.Name(), iniArray.Values(), iniArray.RawLines() );
            break;
        }    

        case IniLine::TYPE_INVALID:
            CARAMEL_THROW( "Line: %u : Syntax error in %s section", lineNo, m_currSection->GetName() );

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
        CARAMEL_THROW( "Section duplicate, section name: %s", sectionName );
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


//
// Value Accessors
//

Bool IniSection::HasValue( const std::string& valueName ) const
{
    return m_impl->HasValue( valueName );
}


Bool IniSection::GetBoolValue( const std::string& valueName ) const
{
    const std::string value = m_impl->GetStringValue( valueName );

    Lexical::Boolean bvalue;
    if ( bvalue.TryParse( value ))
    {
        return bvalue;
    }

    CARAMEL_THROW( "Can't convert value %s \"%s\" to Bool, in section %s",
                   valueName, value, m_impl->GetName() );
}


Int IniSection::GetIntValue( const std::string& valueName ) const
{
    const std::string value = m_impl->GetStringValue( valueName );

    Lexical::Integer< Int > ivalue;
    if ( ivalue.TryParse( value ))
    {
        return ivalue;
    }

    CARAMEL_THROW( "Can't convert value %s \"%s\" to Int, in section %s",
                   valueName, value, m_impl->GetName() );
}


Uint IniSection::GetUintValue( const std::string& valueName ) const
{
    const std::string value = m_impl->GetStringValue( valueName );

    Lexical::Integer< Uint > uvalue;
    if ( uvalue.TryParse( value ))
    {
        return uvalue;
    }

    CARAMEL_THROW( "Can't convert value %s \"%s\" to Int, in section %s",
                   valueName, value, m_impl->GetName() );
}


Float IniSection::GetFloatValue( const std::string& valueName ) const
{
    CARAMEL_NOT_IMPLEMENTED();
}


std::string IniSection::GetStringValue( const std::string& valueName ) const
{
    return m_impl->GetStringValue( valueName );
}


std::vector< std::string > IniSection::GetStringArrayValue( const std::string& valueName ) const
{
    return m_impl->GetStringArrayValue( valueName );
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
    return m_values.end()      != m_values.find( valueName )
        || m_arrayValues.end() != m_arrayValues.find( valueName );
}


std::string IniSectionImpl::GetStringValue( const std::string& valueName ) const
{
    ValueMap::const_iterator ivalue = m_values.find( valueName );
    if ( m_values.end() != ivalue )
    {
        return ivalue->second.value;
    }

    ArrayValueMap::const_iterator iarray = m_arrayValues.find( valueName );
    if ( m_arrayValues.end() != iarray )
    {
        const std::vector< std::string >& values = iarray->second.values;
        
        if ( values.empty() ) { return std::string(); }

        std::string result = values[0];
        const std::string sep( "," );
        for ( Uint i = 1; i < values.size(); ++ i )
        {
            result += sep + values[i];
        }

        return result;
    }

    CARAMEL_THROW( "Value %s not found in section: %s", valueName, m_name );
}


std::vector< std::string > IniSectionImpl::GetStringArrayValue( const std::string& valueName ) const
{
    ArrayValueMap::const_iterator iarray = m_arrayValues.find( valueName );
    if ( m_arrayValues.end() != iarray )
    {
        return iarray->second.values;
    }

    CARAMEL_THROW( "Value %s not found in section: %s", valueName, m_name );
}

//
// Manipulations
//

void IniSectionImpl::AddValue(
    const std::string& valueName, const std::string& inputValue, const std::string& inputRawLine )
{
    if ( this->HasValue( valueName ))
    {
        CARAMEL_THROW( "Duplicate value %s in section %s", valueName, m_name );
    }

    ValueEntry value;
    value.value = inputValue;
    value.rawLineIndex = m_rawLines.size();

    m_values.insert( std::make_pair( valueName, value ));

    RawLineEntry rawLine;
    rawLine.rawLine = inputRawLine;
    rawLine.valueName = valueName;

    m_rawLines.push_back( rawLine );
}


void IniSectionImpl::AddArrayValue(
    const std::string& valueName,
    const std::vector< std::string >& inputValues,
    const std::vector< std::string >& inputRawLines )
{
    if ( this->HasValue( valueName ))
    {
        CARAMEL_THROW( "Duplicate value %s in section %s", valueName, m_name );
    }

    RawLineEntry rawLine;
    for ( Uint i = 0; i < inputRawLines.size(); ++ i )
    {
        rawLine.rawLine = inputRawLines[i];
        m_rawLines.push_back( rawLine );
    }

    ArrayValueEntry value;
    value.values = inputValues;
    value.lastRawLineIndex = m_rawLines.size();
    m_arrayValues.insert( std::make_pair( valueName, value ));
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
    Uint pos = 0;
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


    std::smatch matches;
    const std::regex section    ( "\\[(.*)\\]" );
    const std::regex arrayBegin ( "([^=\\s]*)\\[\\]\\s*=\\s*\\{.*" );
    const std::regex quotedValue( "([^=\\s]*)\\s*=\\s*\"([^\"]*)\"" );
    const std::regex value      ( "([^=\\s]*)\\s*=\\s*([^\\s]*)" );

    if ( std::regex_match( line, matches, section ))
    {
        m_type = TYPE_SECTION;
        m_name = matches[1];
    }
    else if ( std::regex_match( line, matches, arrayBegin ))
    {
        m_type = TYPE_ARRAY_BEGIN;
        m_name = matches[1];
    }
    else if ( std::regex_match( line, matches, quotedValue ))
    {
        // REMARKS: You must match 'quotedValue' before 'value'.

        m_type = TYPE_VALUE;
        m_name = matches[1];
        m_value = matches[2];
        m_valueBegin = matches.position( 2 );
        m_quoted = true;
    }
    else if ( std::regex_match( line, matches, value ))
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
//
// INI Array
//

IniArray::IniArray( const std::string& firstRawLine )
    : m_firstRawLine( firstRawLine )
    , m_failed( false )
{
}


Bool IniArray::TryRead( TextReader& reader, Uint& lineNo )
{
    const std::string line = RemoveCommentsAndTrim( m_firstRawLine );
    const std::string values = AfterFirst( line, '{' );

    -- lineNo;  // The first raw line would be counted again.

    std::string rawLine = values;
    while ( this->ParseLine( values, lineNo ))
    {
        if ( ! reader.ReadLine( rawLine ))
        {
            return false;
        }
    }

    return ! m_failed;
}


Bool IniArray::ParseLine( const std::string& rawLine, Uint& lineNo )
{
    ++ lineNo;
    m_rawLines.push_back( rawLine );

    const std::string line = RemoveCommentsAndTrim( rawLine );

    if ( ! ( EndsWith( line, ',' ) || EndsWith( line, '}' )))
    {
        m_failed = true;
        return false;
    }

    const std::string values = line.substr( 0, line.length() - 1 );

    const boost::char_separator< Char > sep( "," );
    const boost::tokenizer< boost::char_separator< Char > > tokzer( values, sep );
    std::vector< std::string > tokens( tokzer.begin(), tokzer.end() );

    for ( Uint i = 0; i < tokens.size(); ++ i )
    {
        std::string value( tokens[i] );
        Trim( value );
        m_values.push_back( value );
    }

    return ! EndsWith( line, '}' );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
