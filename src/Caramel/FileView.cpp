// Caramel C++ Library - File View Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/FileView/IniFileViewImpl.h>
#include <Caramel/FileView/IniSectionImpl.h>
#include <Caramel/FileView/IniSyntax.h>
#include <Caramel/Io/InputFileStream.h>
#include <Caramel/Io/TextStreamReader.h>
#include <Caramel/Lexical/Boolean.h>
#include <Caramel/Lexical/Integer.h>
#include <regex>


namespace Caramel
{

//
// Contents
//
//   IniFileView
//   IniSection
//   IniSyntax
//

///////////////////////////////////////////////////////////////////////////////
//
// INI File View
//

IniFileView::IniFileView()
    : m_impl( new IniFileViewImpl )
{
}


IniFileView::IniFileView( const Utf8String& fileName )
    : m_impl( new IniFileViewImpl )
{
    this->LoadFromFile( fileName );
}


IniFileView::~IniFileView()
{
}


void IniFileView::LoadFromFile( const Utf8String& fileName )
{
    const Path inputPath( fileName );

    const Path fullPath = inputPath.HasExtension()
                        ? inputPath
                        : inputPath.AppendExtension( "ini" );

    InputFileStream file( fullPath );
    TextStreamReader reader( file );

    m_impl->LoadFromText( reader );
}


void IniFileView::LoadFromText( TextReader& reader )
{
    m_impl->LoadFromText( reader );
}


IniSection IniFileView::GetSection( const std::string& sectionName )
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

IniFileViewImpl::IniFileViewImpl()
    : m_textEncoding( TEXT_ENCODING_UTF8 )
    , m_currSection( nullptr )
{
}


void IniFileViewImpl::LoadFromText( TextReader& reader )
{
    this->Clear();
    this->AddSection( "", Utf8String() );

    Uint lineNo = 0;
    Utf8String rawLine;
    while ( reader.ReadLine( rawLine ))
    {
        ++ lineNo;

        IniSyntax syntax( rawLine );

        switch ( syntax.Type() )
        {
        case IniSyntax::TYPE_BLANK:
            m_currSection->AddRawLine( rawLine );
            break;

        case IniSyntax::TYPE_SECTION:
            this->AddSection( syntax.Name(), rawLine );
            break;

        case IniSyntax::TYPE_VALUE:
            m_currSection->AddValue( syntax.Name(), syntax.Value(), rawLine );
            break;

        case IniSyntax::TYPE_INVALID:
            CARAMEL_THROW( "Syntax error in %s section", m_currSection->GetName() );

        default:
            CARAMEL_NOT_REACHED();
        }
    }
}


//
// Manipulators
//

void IniFileViewImpl::Clear()
{
    m_currSection.reset();
    m_sectionMap.clear();
    m_sectionSeq.clear();
}


//
// Section Management
//

void IniFileViewImpl::AddSection( const std::string& sectionName, const Utf8String& rawLine )
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


IniSectionPtr IniFileViewImpl::FindSection( const std::string& sectionName ) const
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
    const Utf8String value = m_impl->GetStringValue( valueName );

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
    const Utf8String value = m_impl->GetStringValue( valueName );

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
    const Utf8String value = m_impl->GetStringValue( valueName );

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


Utf8String IniSection::GetStringValue( const std::string& valueName ) const
{
    return m_impl->GetStringValue( valueName );
}


std::vector< Utf8String > IniSection::GetStringArrayValue( const std::string& valueName ) const
{
    CARAMEL_NOT_IMPLEMENTED();
}


//
// Implementation
//

IniSectionImpl::IniSectionImpl( const std::string& name, const Utf8String& rawLine )
    : m_name( name )
{
    if ( ! rawLine.IsEmpty() )
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


Utf8String IniSectionImpl::GetStringValue( const std::string& valueName ) const
{
    ValueMap::const_iterator ivalue = m_values.find( valueName );
    if ( m_values.end() == ivalue )
    {
        CARAMEL_THROW( "Value %s not found in section: %s", valueName, m_name );
    }

    return ivalue->second.value;
}


//
// Manipulations
//

void IniSectionImpl::AddValue(
    const std::string& valueName, const Utf8String& inputValue, const Utf8String& inputRawLine )
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


void IniSectionImpl::AddRawLine( const Utf8String& inputRawLine )
{
    RawLineEntry rawLine;
    rawLine.rawLine = inputRawLine;

    m_rawLines.push_back( rawLine );
}


///////////////////////////////////////////////////////////////////////////////
//
// INI Syntax
//

IniSyntax::IniSyntax( const Utf8String& rawLine )
    : m_rawLine( rawLine )
    , m_type( TYPE_UNDEF )
    , m_valueBegin( -1 )
    , m_quoted( false )
{
    this->Parse();
}


void IniSyntax::Parse()
{
    // Step 1 : Trim out the comments and white-spaces.

    Uint pos = 0;
    Bool quoted = false;
    while ( pos < m_rawLine.Length() )
    {
        const Char c = m_rawLine[ pos ];
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

    const Utf8String line = m_rawLine.Substr( 0, pos );

    if ( line.Trim().IsEmpty() )
    {
        m_type = TYPE_BLANK;
        return;
    }


    // Step 2 : Parse the value or section

    // REMARKS: You can't pass a temporary variable to std::regex_match().
    //          Therefore you need to copy line to a std::string before matching.
    const std::string sline = line.ToString(); 

    std::smatch matches;
    const std::regex section( "\\s*\\[(.*)\\]\\s*" );
    const std::regex quotedValue( "\\s*([^=\\s]*)\\s*=\\s*\"([^\"]*)\"\\s*" );
    const std::regex value( "\\s*([^=\\s]*)\\s*=\\s*([^\\s]*)\\s*" );

    if ( std::regex_match( sline, matches, section ))
    {
        m_type = TYPE_SECTION;
        m_name = matches[1];
    }
    else if ( std::regex_match( sline, matches, quotedValue ))
    {
        // REMARKS: You must match 'quotedValue' before 'value'.

        m_type = TYPE_VALUE;
        m_name = matches[1];
        m_value = Utf8String( matches[2] );
        m_valueBegin = matches.position( 2 );
        m_quoted = true;
    }
    else if ( std::regex_match( sline, matches, value ))
    {
        m_type = TYPE_VALUE;
        m_name = matches[1];
        m_value = Utf8String( matches[2] );
        m_valueBegin = matches.position( 2 );
    }
    else
    {
        m_type = TYPE_INVALID;
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
