// Caramel C++ Library - Value Facility - Detail - Any Holders Header

#ifndef __CARAMEL_VALUE_DETAIL_ANY_HOLDERS
#define __CARAMEL_VALUE_DETAIL_ANY_HOLDERS
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Error/Exception.h>
#include <Caramel/Meta/IfThenElse.h>
#include <Caramel/Meta/IsGeneralString.h>
#include <type_traits>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Holder
// - Abstract class.
//

class AnyHolder
{
public:
    virtual ~AnyHolder() {}
};


//
// Any Number
// - For numeric fundamental types
//

class AnyNumberImpl;

class AnyNumber : public AnyHolder
{
public:
    
    explicit AnyNumber( Int value );
    explicit AnyNumber( Uint value );

    ~AnyNumber();
    

    /// Retrieve Value ///

    template< typename T >
    static T CastTo( const AnyHolder* holder )
    {
        auto number = dynamic_cast< const AnyNumber* >( holder );
        if ( ! number )
        {
            CARAMEL_THROW( "Not a Any Number type" );
        }

        T value = 0;
        number->Get( value );
        return value;        
    }


    void Get( Int& value ) const;
    void Get( Uint& value ) const;


private:
    std::unique_ptr< AnyNumberImpl > m_impl;
};


//
// Any String
//

class AnyString : public AnyHolder
{
public:

    explicit AnyString( const std::string& s );
    explicit AnyString( const Char* sz );


    //
    // Retrieve Value
    // - AnyString can only retrieve value by std::string type.
    //
    template< typename T >
    static T CastTo( const AnyHolder* holder )
    {
        static_assert( std::is_same< T, std::string >::value, "T must be std::string" );

        auto astring = dynamic_cast< const AnyString* >( holder );
        if ( ! astring )
        {
            CARAMEL_THROW( "Not a Any String type" );
        }

        return astring->m_value;
    }


private:
    
    std::string m_value;    
};


//
// Any Object
// - All types other than numerica or string.
//

template< typename T >
class AnyObject : public AnyHolder
{
};


//
// Holder Select
//

template< typename T >
struct AnyHolderSelect
{
    typedef typename IfThenElse2T
    <
        std::is_arithmetic< T >::value, AnyNumber,
        IsGeneralString< T >::VALUE,    AnyString,
                                        AnyObject< T >
    >::Type Type;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_VALUE_DETAIL_ANY_HOLDERS
