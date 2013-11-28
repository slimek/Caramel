// Caramel C++ Library - Value Facility - Implementation

#include "CaramelPch.h"

#include "Value/NamedValuesImpl.h"
#include <Caramel/Lexical/Boolean.h>
#include <Caramel/Lexical/Floating.h>
#include <Caramel/Lexical/Integer.h>


namespace Caramel
{

//
// Contents
//
//   NamedValues
//   ConstNamedValueRef
//   NamedValueRef
//   NamedValueEntry
//

///////////////////////////////////////////////////////////////////////////////
//
// Named Values
//

NamedValues::NamedValues()
    : m_impl( new NamedValuesImpl )
{
}


//
// Accessors
//

Detail::NamedValueRef NamedValues::operator[]( const std::string& name )
{
    Detail::NamedValueEntry* entry = nullptr;

    auto ientry = m_impl->m_valueEntries.find( name );
    if ( m_impl->m_valueEntries.end() != ientry )
    {
        entry = &( ientry->second );
    }

    return Detail::NamedValueRef( this, name, entry );
}


Detail::ConstNamedValueRef NamedValues::operator[]( const std::string& name ) const
{
    auto ientry = m_impl->m_valueEntries.find( name );
    if ( m_impl->m_valueEntries.end() == ientry )
    {
        CARAMEL_THROW( "Value not found, name: %s", name );
    }

    return Detail::ConstNamedValueRef( name, &( ientry->second ));
}


//
// Implementation
//

Detail::NamedValueEntry* NamedValuesImpl::InsertValue( const std::string& name )
{
    return &m_valueEntries[ name ];
}


namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Constant Named Value Reference
//

ConstNamedValueRef::ConstNamedValueRef( const std::string& name, NamedValueEntry* entry )
    : m_name( name )
    , m_entry( entry )
{
}


//
// Accessors 
//

Bool ConstNamedValueRef::AsBool() const
{
    return m_entry->GetBool();
}


Int ConstNamedValueRef::AsInt() const
{
    switch ( m_entry->type )
    {
    case NAMED_VALUE_BOOL:
    case NAMED_VALUE_INT:
    case NAMED_VALUE_UINT:
        return m_entry->GetInt();

    case NAMED_VALUE_STRING:
    {
        Lexical::Integer< Int > xint;
        if ( ! xint.TryParse( m_entry->GetString() ))
        {
            CARAMEL_THROW( "Can't convert string value to int, name: %s", m_name );
        }
        return xint;
    }

    case NAMED_VALUE_DOUBLE:
        CARAMEL_THROW( "Can't convert double value to int, name: %s", m_name );
    
    default:
        CARAMEL_NOT_REACHED();
    }
}


Uint ConstNamedValueRef::AsUint() const
{
    switch ( m_entry->type )
    {
    case NAMED_VALUE_BOOL:
    case NAMED_VALUE_INT:
    case NAMED_VALUE_UINT:
        return m_entry->GetUint();

    case NAMED_VALUE_STRING:
    {
        Lexical::Integer< Uint > xuint;
        if ( ! xuint.TryParse( m_entry->GetString() ))
        {
            CARAMEL_THROW( "Can't convert string value to uint, name: %s", m_name );
        }
        return xuint;
    }

    case NAMED_VALUE_DOUBLE:
        CARAMEL_THROW( "Can't convert double value to uint, name: %s", m_name );
    
    default:
        CARAMEL_NOT_REACHED();
    }
}


Double ConstNamedValueRef::AsDouble() const
{
    return m_entry->GetDouble();
}


std::string ConstNamedValueRef::AsString() const
{
    return m_entry->GetString();
}


///////////////////////////////////////////////////////////////////////////////
//
// Name Value Reference
//

NamedValueRef::NamedValueRef( NamedValues* host, const std::string& name, NamedValueEntry* entry )
    : ConstNamedValueRef( name, entry )
    , m_host( host )
{
}


NamedValueRef& NamedValueRef::operator=( Bool value )
{
    this->PrepareEntry();

    m_entry->value = ( value ? 1u : 0u );
    m_entry->type  = NAMED_VALUE_BOOL;

    return *this;
}


NamedValueRef& NamedValueRef::operator=( Int value )
{
    this->PrepareEntry();

    m_entry->value = static_cast< Uint >( value );
    m_entry->type  = NAMED_VALUE_INT;

    return *this;
}


NamedValueRef& NamedValueRef::operator=( Uint value )
{
    this->PrepareEntry();

    m_entry->value = value;
    m_entry->type  = NAMED_VALUE_UINT;

    return *this;
}


NamedValueRef& NamedValueRef::operator=( Double value )
{
    this->PrepareEntry();

    m_entry->value = value;
    m_entry->type  = NAMED_VALUE_DOUBLE;

    return *this;
}


NamedValueRef& NamedValueRef::operator=( const std::string& value )
{
    this->PrepareEntry();

    m_entry->value = value;
    m_entry->type  = NAMED_VALUE_STRING;

    return *this;
}


NamedValueRef& NamedValueRef::operator=( const Char* value )
{
    if ( ! value )
    {
        CARAMEL_INVALID_ARGUMENT();
    }

    return this->operator=( std::string( value ));
}


void NamedValueRef::PrepareEntry()
{
    if ( ! m_entry )
    {
        m_entry = m_host->m_impl->InsertValue( m_name );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Named Value Entry
//

Bool NamedValueEntry::GetBool() const
{
    return 0 != boost::get< Uint >( value );
}


Int NamedValueEntry::GetInt() const
{
    return static_cast< Int >( boost::get< Uint >( value ));
}


Uint NamedValueEntry::GetUint() const
{
    return boost::get< Uint >( value );
}


Double NamedValueEntry::GetDouble() const
{
    return boost::get< Double >( value );
}


std::string NamedValueEntry::GetString() const
{
    return boost::get< std::string >( value );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel
