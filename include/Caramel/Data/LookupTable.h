// Caramel C++ Library - Data Facility - Lookup Table Header

#ifndef __CARAMEL_DATA_LOOKUP_TABLE_H
#define __CARAMEL_DATA_LOOKUP_TABLE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Data/PlainTypes.h>
#include <Caramel/Lexical/Integer.h>
#include <Caramel/Numeric/NumberTraits.h>
#include <Caramel/String/CainLess.h>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Lookup Table
// - A Bi-directional table for integer/enum values and their names.
//   The string comparison is always case-insensitive.
//
//   USAGE:
//
//     const auto images = Caramel::LookupTable< ImageType >
//         ( IMAGE_PNG, "png" )
//         ( IMAGE_JPG, "jpg", "jpeg" )   // with up to 2 aliases
//         ( IMAGE_GIF, "gif" );
//
//     ImageFormat image = IMAGE_UNDEF;
//     if ( table.FindValueByName( imageName, image ))
//     { ... }
//     

template< typename ValueType >
class LookupTable
{
    static_assert(
        std::is_integral< ValueType >::value || std::is_enum< ValueType >::value,
        "ValueType must be an integer or enum type"
    );

    static_assert(
        sizeof( Int32 ) >= sizeof( typename NumberTraits< ValueType >::NumberType ),
        "LookupTable doesn't support 64-bit type"
    );

public:

    /// Building Table ///

    LookupTable( ValueType value, const std::string& name );
    LookupTable( ValueType value, const std::string& name, const std::string& alias );
    LookupTable(
        ValueType value, const std::string& name,
        const std::string& alias1, const std::string& alias2 );

    LookupTable&& operator()( ValueType value, const std::string& name );
    LookupTable&& operator()( ValueType value, const std::string& name, const std::string& alias );
    LookupTable&& operator()(
        ValueType value, const std::string& name,
        const std::string& alias1, const std::string& alias2 );


    // Imbue from a pair array, in ( enum, name ) format.
    template< typename PairType, Uint size >
    explicit LookupTable( const PairType (& table)[size] );


    //
    // Searching
    //
    //   FindValueByInt  : Find by an integer value. It is useful for enum types.
    //   FindValueByText : The text may be the name, or represent the integer value.
    //

    Bool FindValueByName( const std::string& name, ValueType& value ) const;
    Bool FindValueByInt ( Int32 intValue, ValueType& enumValue ) const;

    Bool FindValueByText( const std::string& text, ValueType& value ) const;

    Bool FindName( ValueType value, std::string& name ) const;

    Bool ContainsValue( Int32 value ) const;
    Bool ContainsName( const std::string& name ) const;


private:
    
    //
    // Boost.Bimap< Enum, String >
    // - Left  is Enum -> Name
    //   Right is Name -> Enum
    //
    typedef typename boost::bimaps::bimap <
        boost::bimaps::multiset_of< ValueType >,
        boost::bimaps::set_of< std::string, CainLess >
    > TableType;

    typedef typename TableType::value_type TableValue;

    TableType m_table;

};


//
// Making Function
// - Make a LookupTable for data member.
// 
//   Example:
//
//   MyClass::MyClass()
//      : m_table( MakeLookupTable( 1, "one" )( 2, "two" ) ... )
//

template< typename ValueType >
inline LookupTable< ValueType > MakeLookupTable( ValueType value, const std::string& name )
{
    return LookupTable< ValueType >( value, name );
}


template< typename ValueType >
inline LookupTable< ValueType > MakeLookupTable(
    ValueType value, const std::string& name, const std::string& alias )
{
    return LookupTable< ValueType >( value, name, alias );
}


template< typename ValueType >
inline LookupTable< ValueType > MakeLookupTable(
    ValueType value, const std::string& name,
    const std::string& alias1, const std::string& alias2 )
{
    return LookupTable< ValueType >( value, name, alias1, alias2 );
}


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

template< typename ValueType >
inline LookupTable< ValueType >::LookupTable( ValueType value, const std::string& name )
{
    m_table.insert( TableValue( value, name ));
}


template< typename ValueType >
inline LookupTable< ValueType >::LookupTable(
    ValueType value, const std::string& name, const std::string& alias )
{
    m_table.insert( TableValue( value, name ));
    m_table.insert( TableValue( value, alias ));
}


template< typename ValueType >
inline LookupTable< ValueType >::LookupTable(
    ValueType value, const std::string& name,
    const std::string& alias1, const std::string& alias2 )
{
    m_table.insert( TableValue( value, name ));
    m_table.insert( TableValue( value, alias1 ));
    m_table.insert( TableValue( value, alias2 ));
}


template< typename ValueType >
inline LookupTable< ValueType >&& LookupTable< ValueType >::operator()(
    ValueType value, const std::string& name )
{
    m_table.insert( TableValue( value, name ));
    return std::move( *this );
}


template< typename ValueType >
inline LookupTable< ValueType >&& LookupTable< ValueType >::operator()(
    ValueType value, const std::string& name, const std::string& alias )
{
    m_table.insert( TableValue( value, name ));
    m_table.insert( TableValue( value, alias ));
    return std::move( *this );
}


template< typename ValueType >
inline LookupTable< ValueType >&& LookupTable< ValueType >::operator()(
    ValueType value, const std::string& name,
    const std::string& alias1, const std::string& alias2 )
{
    m_table.insert( TableValue( value, name ));
    m_table.insert( TableValue( value, alias1 ));
    m_table.insert( TableValue( value, alias2 ));
    return std::move( *this );
}


template< typename ValueType >
template< typename PairType, Uint size >
inline LookupTable< ValueType >::LookupTable( const PairType (& table)[size] )
{
    for ( const auto& valueName : table )
    {
        m_table.insert( TableValue( valueName.first, valueName.second ));
    }
}


//
// Searching
//

template< typename ValueType >
inline Bool LookupTable< ValueType >::FindValueByName( const std::string& name, ValueType& value ) const
{
    const auto iname = m_table.right.find( name );
    if ( m_table.right.end() == iname ) { return false; }

    value = iname->second;
    return true;
}


template< typename ValueType >
inline Bool LookupTable< ValueType >::FindValueByInt( Int32 intValue, ValueType& enumValue ) const
{
    const auto ienum = m_table.left.find( static_cast< ValueType >( intValue ));
    if ( m_table.left.end() == ienum ) { return false; }

    enumValue = ienum->first;
    return true;
}


template< typename ValueType >
inline Bool LookupTable< ValueType >::FindValueByText( const std::string& text, ValueType& value ) const
{
    Lexical::Integer< Int32 > ivalue;

    if ( ivalue.TryParse( text ))
    {
        return this->FindValueByInt( ivalue, value );
    }
    else
    {
        return this->FindValueByName( text, value );
    }
}


template< typename ValueType >
inline Bool LookupTable< ValueType >::FindName( ValueType value, std::string& name ) const
{
    const auto iname = m_table.left.find( value );
    if ( m_table.left.end() == iname ) { return false; }

    name = iname->second;
    return true;
}


template< typename ValueType >
inline Bool LookupTable< ValueType >::ContainsName( const std::string& name ) const
{
    return m_table.right.end() != m_table.right.find( name );
}


template< typename ValueType >
inline Bool LookupTable< ValueType >::ContainsValue( Int32 value ) const
{
    return m_table.left.end() != m_table.left.find( static_cast< ValueType >( value ));
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_DATA_LOOKUP_TABLE_H
