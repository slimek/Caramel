// Caramel C++ Library - Value Facility - Any Header

#ifndef __CARAMEL_VALUE_ANY_H
#define __CARAMEL_VALUE_ANY_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Value/Detail/AnyCasters.h>
#include <Caramel/Value/Detail/AnyHolders.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any
// - This class allow you to transfer "any" type of data.
//
//   The input and output types may be different for some numeric types.
//   Convertion may throw exception if the output type can't represent
//   the input value exactly.
//
//     Output   |   Input Categories   |  Input Types
//   ------------------------------------------------------
//     Boolean  <=  Boolean            |  Bool 
//     Integer  <=  Integer / Enum     |  Int/Uint, any enums
//     Floating <=  Floating / Integer |  Float/Double, Int/Uint
//     String   <=  String             |  std::string, Char*
//     Enum     <=  Enum               |  enum
//     Object   <=  Object             |  other types
//

class Any
{
public:

    Any() {}

    template< typename T >
    Any( const T& value );

    template< typename T >
    Any& operator=( const T& value );

    
    /// Retrieve Value ///

    template< typename T >
    T As() const;


    /// Properties ///

    Bool IsEmpty() const { return ! m_holder; }


private:
    std::shared_ptr< Detail::AnyHolder > m_holder;
        
};


//
// Stand-alone Creators
// - For polymorphic work-around. Example:
//
//   auto any = MakeAny< Base >( derived );
//

template< typename T >
inline Any MakeAny( const T& value )
{
    return Any( value );
}


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename T >
inline Any::Any( const T& value )
    : m_holder( new typename Detail::AnyHolderSelect< T >::Type( value ))
{
}


template< typename T >
inline Any& Any::operator=( const T& value )
{
    m_holder.reset( new typename Detail::AnyHolderSelect< T >::Type( value ));
    return *this;
}


template< typename T >
inline T Any::As() const
{
    typedef typename Detail::AnyCasterSelect< T >::Type Caster;
    return Caster::template CastTo< T >( m_holder.get() );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_VALUE_ANY_H
