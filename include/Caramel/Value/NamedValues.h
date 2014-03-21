// Caramel C++ Library - Value Facility - Named Values Header

#ifndef __CARAMEL_VALUE_NAMED_VALUES_H
#define __CARAMEL_VALUE_NAMED_VALUES_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Value/Detail/NamedValueRef.h>
#include <map>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Named Values
// - A general name-value pair collections.
//   Supporting value types: Bool, Int, Uint, Int64, Double, std::string.
//
// USAGE:
//
// < Adding Values >
// 1. Add values by operator[], or
//
//    Caramel::NamedValues nv;
//    nv[ "name" ]   = "Reimu";
//    nv[ "age" ]    = 16;
//    nv[ "canFly" ] = true;
//
// 2. Make values by chaining, fit for function parameters.
//
//    player->InitSettings( Caramel::NamedValues
//        ( "name",   "Reimu" )
//        ( "age",     16 )
//        ( "canFly", true )
//    );
//
// < Getting Values >
// Access values by "AsXxx" functions.
//
//    m_name   = nv[ "name" ].AsString();
//    m_age    = nv[ "age" ].AsInt();
//    m_canFly = nv[ "canFly" ].AsBool();
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

    Bool IsEmpty() const;
    Uint Size()    const;


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
