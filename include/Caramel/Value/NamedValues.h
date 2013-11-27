// Caramel C++ Library - Value Facility - Named Values Header

#ifndef __CARAMEL_VALUE_NAMED_VALUES_H
#define __CARAMEL_VALUE_NAMED_VALUES_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Value/Detail/NamedValueRef.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Named Values
// - Copy-on-write.
//

class NamedValuesImpl;

class NamedValues
{
    friend class Detail::NamedValueRef;

public:

    NamedValues();
    
    Detail::NamedValueRef      operator[]( const std::string& name );
    Detail::ConstNamedValueRef operator[]( const std::string& name ) const;


private:

    std::shared_ptr< NamedValuesImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_VALUE_NAMED_VALUES_H
