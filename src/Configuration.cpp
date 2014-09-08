// Caramel C++ Library - Configuration Facility - Implementation

#include "CaramelPch.h"

#include "Configuration/ConfigManager.h"
#include "Configuration/ConfigRootImpl.h"
#include "Configuration/ConfigSectionImpl.h"
#include <Caramel/Configuration/ConfigValues.h>
#include <Caramel/Document/IniDocument.h>
#include <Caramel/Thread/MutexLocks.h>


namespace Caramel
{

//
// Contents
//
//   ConfigManager
//   ConfigRoot
//   ConfigReader
//   ConfigSection
//   ConfigValue
//   ConfigBool
//   ConfigInt
//   ConfigString
//

///////////////////////////////////////////////////////////////////////////////
//
// Configuration Manager
//

ConfigManager::ConfigManager()
    : m_root( new ConfigRootImpl )
{
}


///////////////////////////////////////////////////////////////////////////////
//
// Configuration Root
// - TODO: Allow multiple roots, accessed by name.
//

ConfigRoot::ConfigRoot()
    : m_impl( ConfigManager::Instance()->GetRoot() )
{    
}


void ConfigRoot::Load( const std::map< std::string, NamedValues >& sectionMap )
{
    m_impl->Load( sectionMap );
}


//
// Implementation
//

void ConfigRootImpl::AddSection( ConfigSectionPtr section )
{
    if ( ! m_sections.Insert( section->GetName(), section ))
    {
        CARAMEL_THROW( "Section %s duplicate", section->GetName() );
    }
}


void ConfigRootImpl::Load( const std::map< std::string, NamedValues >& sectionMap )
{
    auto sections = m_sections.GetValuesSnapshot();

    for ( auto section : sections )
    {
        const std::string sectName = section->GetName();

        const auto iter = sectionMap.find( sectName );
        if ( iter == sectionMap.end() )
        {
            CARAMEL_THROW( "Section %s not found", sectName );
        }

        section->Load( iter->second );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Configuration Section
//

ConfigSection::ConfigSection( const std::string& name )
    : m_impl( new ConfigSectionImpl( name ))
{
    auto root = ConfigManager::Instance()->GetRoot();
    root->AddSection( m_impl );
}


void ConfigSection::AddValue( ConfigValue& value )
{
    m_impl->AddValue( &value );
}


//
// Implementation
//

ConfigSectionImpl::ConfigSectionImpl( const std::string& name )
    : m_name( name )
{
}


void ConfigSectionImpl::AddValue( ConfigValue* value )
{
    if ( ! m_values.Insert( value->GetName(), value ))
    {
        CARAMEL_THROW( "Value %s/%s duplicate", m_name, value->GetName() );
    }
}


void ConfigSectionImpl::Load( const NamedValues& valueData )
{
    auto values = m_values.GetValuesSnapshot();

    for ( auto value : values )
    {
        const std::string valueName = value->GetName();

        if ( ! valueData.HasValue( valueName ))
        {
            if ( value->HasDefault() ) { continue; }

            CARAMEL_THROW( "Value %s/%s not found", m_name, valueName );
        }

        value->Load( valueData );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Configuration Value
//

ConfigValue::ConfigValue( const std::string& name, Bool hasDefault )
    : m_name( name )
    , m_hasDefault( hasDefault )
{
}


///////////////////////////////////////////////////////////////////////////////
//
// Configuration Bool
//

ConfigBool::ConfigBool( ConfigSection& section, const std::string& name )
    : ConfigValue( name, false )
{
    section.AddValue( *this );
}


ConfigBool::ConfigBool( ConfigSection& section, const std::string& name, Bool defaultValue )
    : ConfigValue( name, true )
    , m_value( defaultValue )
{
    section.AddValue( *this );
}


void ConfigBool::Load( const NamedValues& data )
{
    CARAMEL_ASSERT( data.HasValue( m_name ));

    m_value = data[ m_name ].AsBool();
}


///////////////////////////////////////////////////////////////////////////////
//
// Configuration Int
//

ConfigInt::ConfigInt( ConfigSection& section, const std::string& name )
    : ConfigValue( name, false )
{
    section.AddValue( *this );
}


ConfigInt::ConfigInt( ConfigSection& section, const std::string& name, Int defaultValue )
    : ConfigValue( name, true )
    , m_value( defaultValue )
{
    section.AddValue( *this );
}


void ConfigInt::Load( const NamedValues& data )
{
    CARAMEL_ASSERT( data.HasValue( m_name ));

    m_value = data[ m_name ].AsInt();
}


///////////////////////////////////////////////////////////////////////////////
//
// Configuration String
//

ConfigString::ConfigString( ConfigSection& section, const std::string& name )
    : ConfigValue( name, false )
{
    section.AddValue( *this );
}


ConfigString::ConfigString(
    ConfigSection& section, const std::string& name, const std::string& defaultValue )
    : ConfigValue( name, true )
    , m_value( defaultValue )
{
    section.AddValue( *this );
}


void ConfigString::Load( const NamedValues& data )
{
    CARAMEL_ASSERT( data.HasValue( m_name ));

    LockGuard lock( m_mutex );
    m_value = data[ m_name ].AsString();
}


std::string ConfigString::ToString() const
{
    LockGuard lock( m_mutex );
    return m_value;
}


ConfigString::operator std::string() const
{
    return this->ToString();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
