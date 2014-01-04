// Caramel C++ Library - Enum Amenity - Enum Lookup Table Header

#ifndef __CARAMEL_ENUM_LOOKUP_TABLE_H
#define __CARAMEL_ENUM_LOOKUP_TABLE_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Lexical/Integer.h>
#include <Caramel/Numeric/NumberTraits.h>
#include <Caramel/String/CainLess.h>
#include <boost/bimap/bimap.hpp>


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

    EnumLookupTable( EnumType value, const std::string& name );
    EnumLookupTable&& operator()( EnumType value, const std::string& name );


    //
    // Searching
    //
    //   FindEnumByValue : Find the enum of an integer value.
    //   FindEnumByText  : The text may be the name, or represent the integer value.
    //

    Bool FindEnumByName( const std::string& name, EnumType& value ) const;
    Bool FindEnumByValue( Int32 intValue, EnumType& enumValue ) const;

    Bool FindEnumByText( const std::string& text, EnumType& value ) const;

    Bool FindName( EnumType value, std::string& name ) const;

    Bool ContainsValue( Int32 value ) const;
    Bool ContainsName( const std::string& name ) const;


private:
    
    //
    // Boost.Bimap< Enum, String >
    // - Left  is Enum -> Name
    //   Right is Name -> Enum
    //
    typedef typename boost::bimaps::bimap <
        boost::bimaps::set_of< EnumType >,
        boost::bimaps::set_of< std::string, CainLess >
    > TableType;

    typedef typename TableType::value_type TableValue;

    TableType m_table;

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
inline EnumLookupTable< EnumType > EnumLookupChain( EnumType value, const std::string& name )
{
    return EnumLookupTable< EnumType >( value, name );
}


template< typename EnumType >
inline EnumLookupTable< EnumType >::EnumLookupTable( EnumType value, const std::string& name )
{
    m_table.insert( TableValue( value, name ));
}


template< typename EnumType >
inline auto EnumLookupTable< EnumType >::operator()( EnumType value, const std::string& name ) -> EnumLookupTable&&
{
    m_table.insert( TableValue( value, name ));
    return std::move( *this );
}


template< typename EnumType >
inline Bool EnumLookupTable< EnumType >::FindEnumByName( const std::string& name, EnumType& value ) const
{
    const auto iname = m_table.right.find( name );
    if ( m_table.right.end() == iname ) { return false; }

    value = iname->second;
    return true;
}


template< typename EnumType >
inline Bool EnumLookupTable< EnumType >::FindEnumByValue( Int32 intValue, EnumType& enumValue ) const
{
    const auto ienum = m_table.left.find( static_cast< EnumType >( intValue ));
    if ( m_table.left.end() == ienum ) { return false; }

    enumValue = ienum->first;
    return true;
}


template< typename EnumType >
inline Bool EnumLookupTable< EnumType >::FindEnumByText( const std::string& text, EnumType& value ) const
{
    Lexical::Integer< Int32 > ivalue;

    if ( ivalue.TryParse( text ))
    {
        return this->FindEnumByValue( ivalue, value );
    }
    else
    {
        return this->FindEnumByName( text, value );
    }
}


template< typename EnumType >
inline Bool EnumLookupTable< EnumType >::FindName( EnumType value, std::string& name ) const
{
    const auto iname = m_table.left.find( value );
    if ( m_table.left.end() == iname ) { return false; }

    name = iname->second;
    return true;
}


template< typename EnumType >
inline Bool EnumLookupTable< EnumType >::ContainsName( const std::string& name ) const
{
    return m_table.right.end() != m_table.right.find( name );
}


template< typename EnumType >
inline Bool EnumLookupTable< EnumType >::ContainsValue( Int32 value ) const
{
    return m_table.left.end() != m_table.left.find( static_cast< EnumType >( value ));
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ENUM_LOOKUP_TABLE_H
