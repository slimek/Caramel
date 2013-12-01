// Caramel C++ Library - Enum Amenity - Enum Lookup Table Header

#ifndef __CARAMEL_ENUM_LOOKUP_TABLE_H
#define __CARAMEL_ENUM_LOOKUP_TABLE_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Lexical/Integer.h>
#include <Caramel/Numeric/NumberTraits.h>
#include <Caramel/String/CainLess.h>
#include <map>
#include <set>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Enum Lookup Table
// - The string comparison is always case-insensitive.
//

template< typename EnumType >
class EnumLookupTable
{
    static_assert(
        sizeof( Int32 ) >= sizeof( typename NumberTraits< EnumType >::NumberType ),
        "EnumLookupTable doesn't support 64-bit enum type"
    );

public:

    /// Building Table ///

    EnumLookupTable( const std::string& name, EnumType value );
    EnumLookupTable&& operator()( const std::string& name, EnumType value );


    /// Searching ///

    //
    // Find by Text
    // - The text may be the name or represent the integer value.
    //
    Bool Find( const std::string& text, EnumType& value ) const;

    Bool ContainsValue( Int value ) const;
    Bool ContainsName( const std::string& name ) const;


private:
    std::map< std::string, EnumType, CainLess > m_nameTable;
    std::set< Int32 > m_values;
};


//
// Making Function
//
template< typename EnumType >
EnumLookupTable< EnumType > EnumLookupChain( const std::string& name, EnumType value );


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename EnumType >
inline EnumLookupTable< EnumType > EnumLookupChain( const std::string& name, EnumType value )
{
    return EnumLookupTable< EnumType >( name, value );
}


template< typename EnumType >
inline EnumLookupTable< EnumType >::EnumLookupTable( const std::string& name, EnumType value )
{
    m_nameTable.insert( std::make_pair( name, value ));
    m_values.insert( value );
}


template< typename EnumType >
inline auto EnumLookupTable< EnumType >::operator()( const std::string& name, EnumType value ) -> EnumLookupTable&&
{
    m_nameTable.insert( std::make_pair( name, value ));
    m_values.insert( value );

    return std::move( *this );
}


template< typename EnumType >
inline Bool EnumLookupTable< EnumType >::Find( const std::string& text, EnumType& value ) const
{
    Lexical::Integer< Int32 > ivalue;

    if ( ivalue.TryParse( text ))
    {
        if ( m_values.end() == m_values.find( ivalue )) { return false; }

        value = static_cast< EnumType >( static_cast< Int32 >( ivalue ));
        return true;
    }
    else
    {
        auto iter = m_nameTable.find( text );
        if ( m_nameTable.end() == iter ) { return false; }

        value = iter->second;
        return true;
    }
}


template< typename EnumType >
inline Bool EnumLookupTable< EnumType >::ContainsValue( Int value ) const
{
    return m_values.end() != m_values.find( value );
}


template< typename EnumType >
inline Bool EnumLookupTable< EnumType >::ContainsName( const std::string& name ) const
{
    return m_nameTable.end() != m_nameTable.find( name );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ENUM_LOOKUP_TABLE_H
