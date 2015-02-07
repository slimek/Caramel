// Caramel C++ Library - Value Facility - Enum Flags Header

#ifndef __CARAMEL_VALUE_ENUM_FLAGS_H
#define __CARAMEL_VALUE_ENUM_FLAGS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <initializer_list>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Enum Flags
//

template< typename EnumType >
class EnumFlags
{
public:

    EnumFlags();
    EnumFlags( EnumType flags );
    EnumFlags( std::initializer_list< EnumType > flags );


    /// Predicates ///

    // Returns true if all flags in 'testFlags' are matched.
    Bool Match( EnumType testFlags ) const;
    

protected:
  
    typedef typename std::underlying_type< EnumType >::type ValueType;
    ValueType m_value;
};


//
// Implementation
//

template< typename EnumType >
inline EnumFlags< EnumType >::EnumFlags()
    : m_value( 0 )
{}


template< typename EnumType >
inline EnumFlags< EnumType >::EnumFlags( EnumType flags )
    : m_value( static_cast< ValueType >( flags ))
{}


template< typename EnumType >
inline EnumFlags< EnumType >::EnumFlags( std::initializer_list< EnumType > flags )
    : m_value( 0 )
{
    for ( auto flag : flags )
    {
        m_value |= static_cast< ValueType >( flag );
    }
}


template< typename EnumType >
inline Bool EnumFlags< EnumType >::Match( EnumType testFlags ) const
{
    return ( m_value & testFlags ) == testFlags;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_VALUE_ENUM_FLAGS_H
