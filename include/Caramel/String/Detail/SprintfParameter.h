// Caramel C++ Library - String Facility - Detail - Sprintf Parameter Header

#ifndef __CARAMEL_STRING_DETAIL_SPRINTF_PARAMETER_H
#define __CARAMEL_STRING_DETAIL_SPRINTF_PARAMETER_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Meta/IfThenElse.h>
#include <Caramel/String/StringConvertible.h>
#include <type_traits>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Sprintf Parameter Adapters
//

/// Identity Copy, for fundamental and enum types

template< typename T >
class SprintfParameter_IdentityCopy
{
public:
    T operator()( T x ) const { return x; }
};


/// String Convertible ///

template< typename T >
class SprintfParameter_StringConvertible
{
public:
    const Char* operator()( const T& x )
    {
        m_clone = x.ToString();
        return m_clone.c_str();
    }

private:
    std::string m_clone;
};


///////////////////////////////////////////////////////////////////////////////
//
// Sprintf Parameter Select
//

template< typename T >
struct SprintfParameterSelect
{
    typedef typename IfThenElse3T
    <
        std::is_fundamental< T >::value,  SprintfParameter_IdentityCopy< T >,
        std::is_enum< T >::value,         SprintfParameter_IdentityCopy< T >,
        IsStringConvertibleT< T >::VALUE, SprintfParameter_StringConvertible< T >,
                                          EmptyType
    >::Type ParameterType;
};


///////////////////////////////////////////////////////////////////////////////
//
// Sprintf Parameter
//

/// Primary Template ///

template< typename T >
class SprintfParameter
    : public SprintfParameterSelect< T >::ParameterType
{};


//
// Specializations
//

template<>
class SprintfParameter< std::string >
{
public:
    const Char* operator()( const std::string& s ) const { return s.c_str(); }
};


template<>
class SprintfParameter< const Char* >
{
public:
    const Char* operator()( const Char* sz ) const { return sz; }
};


template< Uint n >
class SprintfParameter< const Char[n] >
{
public:
    const Char* operator()( const Char sz[n] ) const { return sz; }
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_STRING_DETAIL_SPRINTF_PARAMETER_H
