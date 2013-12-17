// Caramel C++ Library - Value Facility - Detail - Any Casters Header

#ifndef __CARAMEL_VALUE_DETAIL_ANY_CASTER_H
#define __CARAMEL_VALUE_DETAIL_ANY_CASTER_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Error/Exception.h>
#include <Caramel/Meta/IfThenElse.h>
#include <Caramel/Value/Detail/AnyHolders.h>
#include <type_traits>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Casters
//

//
// Any Integer Caster
// - Accept casting from AnyNumber and AnyEnum
//   NOTES: If holder is an AnyEnum, 64-bits value is not supported.
//

struct AnyIntegerCaster
{
    template< typename T >
    static T CastTo( const AnyHolder* holder )
    {
        static_assert( std::is_integral< T >::value, "Not an integral type" );

        T value = 0;

        auto integer = dynamic_cast< const AnyInteger* >( holder );
        if ( integer )
        {
            integer->Get( value );
            return value;        
        }
        
        auto aenum = dynamic_cast< const AnyEnum* >( holder );
        if ( aenum )
        {
            aenum->Get( value );
            return value;
        }

        CARAMEL_THROW( "Not an AnyNumber or AnyEnum type" );
    }
};


//
// Any Floating Caster
// - Accept casting from AnyNumber
//

struct AnyFloatingCaster
{
    template< typename T >
    static T CastTo( const AnyHolder* holder )
    {
        static_assert( std::is_floating_point< T >::value, "Not a floating type" );

        T value = 0;

        auto integer = dynamic_cast< const AnyInteger* >( holder );
        if ( integer )
        {
            integer->Get( value );
            return value;
        }

        CARAMEL_THROW( "Not an AnyFloating or AnyInteger type" );
    }
};


//
// Any Enum Caster
// - Accept casting from AnyEnum
//

struct AnyEnumCaster
{
    template< typename T >
    static T CastTo( const AnyHolder* holder )
    {
        static_assert( std::is_enum< T >::value, "T must be an enum type" );

        auto aenum = dynamic_cast< const AnyEnum* >( holder );
        if ( ! aenum )
        {
            CARAMEL_THROW( "Not an AnyEnum type" );
        }

        if ( typeid( T ) != aenum->GetType() )
        {
            CARAMEL_THROW( "Enum type not matched" );
        }

        return static_cast< T >( aenum->ToInt64() );
    }
};


//
// Any String Caster
// - Accept casting from AnyString
//

struct AnyStringCaster
{
    template< typename T >
    static T CastTo( const AnyHolder* holder )
    {
        static_assert( std::is_same< T, std::string >::value, "T must be std::string" );

        auto astring = dynamic_cast< const AnyString* >( holder );
        if ( ! astring )
        {
            CARAMEL_THROW( "Not an AnyString type" );
        }

        return astring->Get();
    }
};


//
// Any Object Caster
// - Accept casting from AnyObject
//

struct AnyObjectCaster
{
};


//
// Caster Select
//

template< typename T >
struct AnyCasterSelect
{
    typedef typename IfThenElse4T<
        std::is_integral< T >::value,          AnyIntegerCaster,
        std::is_floating_point< T >::value,    AnyFloatingCaster,
        std::is_enum< T >::value,              AnyEnumCaster,
        std::is_same< T, std::string >::value, AnyStringCaster,
                                               AnyObjectCaster
    >::Type Type;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_VALUE_DETAIL_ANY_CASTER_H
