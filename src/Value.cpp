// Caramel C++ Library - Value Facility - Implementation

#include "CaramelPch.h"

#include "Value/NamedValuesImpl.h"


namespace Caramel
{

//
// Contents
//
//   NamedValues
//   ConstNamedValueRef
//   NameValueRef
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

std::string ConstNamedValueRef::AsString() const
{
    return boost::get< std::string >( m_entry->value );
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


NamedValueRef& NamedValueRef::operator=( const Char* v )
{
    if ( ! v )
    {
        CARAMEL_INVALID_ARGUMENT();
    }

    if ( ! m_entry )
    {
        m_entry = m_host->m_impl->InsertValue( m_name );
    }

    m_entry->value = std::string( v );
    m_entry->type  = NAMED_VALUE_STRING;

    return *this;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel
