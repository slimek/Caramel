// Caramel C++ Library - Value Facility - Detail - Any Holders Header

#ifndef __CARAMEL_VALUE_DETAIL_ANY_HOLDERS
#define __CARAMEL_VALUE_DETAIL_ANY_HOLDERS
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
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
// Any Boolean
// - We forbit the any conversion between boolean and other integers.
//

class AnyBoolean : public AnyHolder
{
public:

    explicit AnyBoolean( Bool value );
  
    /// Retreive Value ///

    Bool Get() const { return m_value; }

private:

    Bool m_value;
};


//
// Any Integer
//

class AnyInteger : public AnyHolder
{
public:

    explicit AnyInteger( Int value );
    explicit AnyInteger( Uint value );
    explicit AnyInteger( Int64 value );
    explicit AnyInteger( Uint64 value );

    /// Retrieve Value ///

    void Get( Int& value ) const;
    void Get( Uint& value ) const;

    void Get( Int64& value ) const;
    void Get( Uint64& value ) const;

    void Get( Float& value ) const;
    void Get( Double& value ) const;

private:

    Bool  m_isUint64;
    Int64 m_value;
};


//
// Any Floating
//

class AnyFloating : public AnyHolder
{
public:

    explicit AnyFloating( Float value );
    explicit AnyFloating( Double value );

    /// Retrieve Value ///

    void Get( Float& value ) const;
    void Get( Double& value ) const;

private:

    Double m_value;
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
// Any Enum
//

class AnyEnum : public AnyHolder
{
public:

    /// Retrieve Value ////

    void Get( Int& value ) const;
    void Get( Uint& value ) const;

    void Get( Int64& value ) const;
    void Get( Uint64& value ) const;

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

    Int64 ToInt64() const override { return static_cast< Int64 > ( m_value ); }

    const std::type_info& GetType() const override { return typeid( T ); }

private:

    T m_value;
};


//
// Any Object
// - All types other than numerica or string.
//

class AnyObject : public AnyHolder
{
public:

    /// Retrieve Value ///

    virtual const Void* GetValue() const = 0;

    /// Type Info ///

    virtual const std::type_info& GetType() const = 0;
};


template< typename T >
class AnyObjectConcrete : public AnyObject
{
public:

    explicit AnyObjectConcrete( const T& value )
        : m_value( value )
    {}

    explicit AnyObjectConcrete( T&& value )
        : m_value( std::move( value ))
    {}

    const Void* GetValue() const override { return &m_value; }

    const std::type_info& GetType() const override { return typeid( T ); }

private:

    T m_value;
};


//
// Holder Select
//

template< typename T >
struct AnyHolderSelect
{
    typedef typename IfThenElse5T
    <
        std::is_same< T, Bool >::value,     AnyBoolean,
        std::is_integral< T >::value,       AnyInteger,
        std::is_floating_point< T >::value, AnyFloating,
        IsGeneralStringT< T >::VALUE,       AnyString,
        std::is_enum< T >::value,           AnyEnumConcrete< T >,
                                            AnyObjectConcrete< T >
    >::Type Type;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_VALUE_DETAIL_ANY_HOLDERS
