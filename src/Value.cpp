// Caramel C++ Library - Value Facility - Implementation

#include "CaramelPch.h"

#include "Value/NamedValuesImpl.h"


namespace Caramel
{

//
// Contents
//
//   NamedValues
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
    return Detail::NamedValueRef( this, name, nullptr );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
