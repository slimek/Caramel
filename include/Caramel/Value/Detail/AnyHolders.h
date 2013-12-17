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

    void Get( Int& value ) const;
    void Get( Uint& value ) const;


private:

    std::unique_ptr< AnyNumberImpl > m_impl;
};


//
// Any Enum
//

class AnyEnum : public AnyHolder
{
public:


    /// Retrieve Value ////

    void Get( Int& value ) const;
    void Get( Uint& value ) const;

    virtual Int64 ToInt64() const = 0;


    /// Type Info ///

    virtual const std::type_info& GetType() const = 0;
};


template< typename T >
class AnyEnumConcrete : public AnyEnum
{
    static_assert( std::is_enum< T >::value, "T must be enum type" );
    static_assert( 4 >= sizeof( T ), "64-bit enum is not supported" );

public:
    
    explicit AnyEnumConcrete( T value )
        : m_value( value )
    {}

    Int64 ToInt64() const { return static_cast< Int64 > ( m_value ); }

    const std::type_info& GetType() const { return typeid( T ); }


private:

    T m_value;
};


//
// Any String
//

class AnyString : public AnyHolder
{
public:

    explicit AnyString( const std::string& s );
    explicit AnyString( const Char* sz );


    /// Retrieve Value ///

    std::string Get() const { return m_value; }


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
    typedef typename IfThenElse3T
    <
        std::is_arithmetic< T >::value, AnyNumber,
        std::is_enum< T >::value,       AnyEnumConcrete< T >,
        IsGeneralString< T >::VALUE,    AnyString,
                                        AnyObject< T >
    >::Type Type;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_VALUE_DETAIL_ANY_HOLDERS
