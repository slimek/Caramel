// Caramel C++ Library - String Facility - Converters Header

#ifndef __CARAMEL_STRING_CONVERTERS_H
#define __CARAMEL_STRING_CONVERTERS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <type_traits>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Integer Converter
//

template< typename T >
class IntegerConverter
{
    static_assert( std::is_integral< T >::value, "T must be an integral type" );

public:
    
    explicit IntegerConverter( T value )
        : m_value( value )
    {}

    std::string ToString() const;
    std::string ToStringWithFixedPoint( Uint digits ) const;

    std::string operator()( const std::string& format ) const;

private:
    
    T m_value;
};


///////////////////////////////////////////////////////////////////////////////
//
// Floating Converter
//

template< typename T >
class FloatingConverter
{
    static_assert( std::is_floating_point< T >::value, "T must be a floating point type" );

public:

    explicit FloatingConverter( T value )
        : m_value( value )
    {}

    std::string ToString() const;
    std::string ToStringWithFixedPoint( Uint digits ) const;

    std::string operator()( const std::string& format ) const;

private:

    T m_value;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_CONVERTERS_H
