// Caramel C++ Library - String Facility - Detail - Format Parameter Header

#ifndef __CARAMEL_STRING_DETAIL_FORMAT_PARAMETER_H
#define __CARAMEL_STRING_DETAIL_FORMAT_PARAMETER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Meta/IfThenElse.h>
#include <Caramel/Numeric/NumberConvertible.h>
#include <Caramel/String/StringConvertible.h>
#include <type_traits>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Format Parameter Adapters
//

//
// Identity Copy, for Fundamental and Enum types.
//
template< typename T >
struct FormatParameter_IdentityCopy
{
    T operator() ( T x ) const { return x; }
};  


//
// String Convertible
//
template< typename T >
struct FormatParameter_StringConvertible
{
    std::string operator() ( const T& x ) const
    {
        return x.ToString();
    }
};


//
// Number Convertible
//
template< typename T >
struct FormatParameter_NumberConvertible
{
    typedef typename T::NumberType NumberType;
    
    NumberType operator() ( const T& x ) const
    {
        return x.ToNumber();
    }
};


///////////////////////////////////////////////////////////////////////////////
//
// Format Parameter Select
//

template< typename T >
struct FormatParameterSelect
{
    typedef typename IfThenElse4T
    <
        std::is_fundamental< T >::value,    FormatParameter_IdentityCopy< T >,
        std::is_enum< T >::value,           FormatParameter_IdentityCopy< T >,
        IsStringConvertibleT< T >::VALUE,   FormatParameter_StringConvertible< T >,
        IsNumberConvertibleT< T >::VALUE,   FormatParameter_NumberConvertible< T >,
                                            EmptyType
    >::Type ParameterType;
};


///////////////////////////////////////////////////////////////////////////////
//
// Format Parameter
//

// Primary Template

template< typename T >
struct FormatParameter
    : public FormatParameterSelect< T >::ParameterType
{};


//
// Specialization for Strings
//

template<>
struct FormatParameter< std::string >
{
    std::string operator() ( const std::string& s ) const { return s; }
};


template<>
struct FormatParameter< Char* >
{
    std::string operator() ( const Char* sz ) const { return std::string( sz ); }
};


//
// C-style literal string
//

template< Uint n >
struct FormatParameter< const Char[n] >
{
    std::string operator() ( const Char(& sz)[n] ) const { return std::string( sz ); }
};


template< Uint n >
struct FormatParameter< Char[n] >
{
    std::string operator() ( const Char(& sz)[n] ) const { return std::string( sz ); }
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_STRING_DETAIL_FORMAT_PARAMETER_H
