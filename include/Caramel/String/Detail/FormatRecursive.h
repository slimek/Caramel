// Caramel C++ Library - String Facility - Detail - Format Recursive Header

#ifndef __CARAMEL_STRING_DETAIL_FORMAT_RECURSIVE_H
#define __CARAMEL_STRING_DETAIL_FORMAT_RECURSIVE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/String/Detail/FormatParameter.h>
#include <Caramel/String/Detail/Formatter.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Format Recursive
//

//
// No argument
//
inline std::string FormatRecursive( Formatter& formatter )
{
    return formatter.GetString();
}


//
// One argument (terminal condition)
//
template< typename T >
inline std::string FormatRecursive( Formatter& formatter, const T& x )
{
    typedef typename std::remove_cv< typename std::remove_reference< T >::type >::type ParamType;

    formatter.Feed( Detail::FormatParameter< ParamType >()( x ));
    return formatter.GetString();
}


//
// Variadic arguments
//
template< typename T, typename... Args >
inline std::string FormatRecursive( Formatter& formatter, const T& x, const Args&... args )
{
    typedef typename std::remove_cv< typename std::remove_reference< T >::type >::type ParamType;

    formatter.Feed( Detail::FormatParameter< ParamType >()( x ));
    return FormatRecursive( formatter, args... );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_STRING_DETAIL_FORMAT_RECURSIVE_H
