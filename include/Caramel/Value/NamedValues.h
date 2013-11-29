// Caramel C++ Library - Value Facility - Named Values Header

#ifndef __CARAMEL_VALUE_NAMED_VALUES_H
#define __CARAMEL_VALUE_NAMED_VALUES_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Value/Detail/NamedValueRef.h>
#include <map>


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
    

    /// Insert Values by Chaining ///

    template< typename T >
    NamedValues( const std::string& name, const T& value );

    template< typename T >
    NamedValues& operator()( const std::string& name, const T& value );


    /// Properties ///

    Uint Size() const;


    /// Access a Value ///

    Detail::NamedValueRef      operator[]( const std::string& name );
    Detail::ConstNamedValueRef operator[]( const std::string& name ) const;


    /// Copy all Values ///

    // Returns all values in ( name, value ) string pairs.
    typedef std::map< std::string, std::string > ValueMap;
    ValueMap GetValueMap() const;


private:

    void Init();

    std::shared_ptr< NamedValuesImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T >
inline NamedValues::NamedValues( const std::string& name, const T& value )
{
    this->Init();
    this->operator[]( name ) = value;
}


template< typename T >
inline NamedValues& NamedValues::operator()( const std::string& name, const T& value )
{
    this->operator[]( name ) = value;
    return *this;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_VALUE_NAMED_VALUES_H
