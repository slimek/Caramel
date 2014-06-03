// Caramel C++ Library - String Facility - Format Header

#ifndef __CARAMEL_STRING_FORMAT_H
#define __CARAMEL_STRING_FORMAT_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/String/Detail/Formatter.h>
#include <Caramel/String/Detail/SprintfParameter.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Format Functions
//


// Functions with no Arguments

inline std::string Format( const Char* format )
{
    return std::string( format );
}


inline const std::string& Format( const std::string& format )
{
    return format;
}


//
// Format with Arguments
//

template< typename T0 >
inline std::string Format( const std::string& format, const T0& a0 )
{
    Detail::Formatter formatter( format );
    formatter.Feed( 0, Detail::SprintfParameter< T0 >()( a0 ));
    return formatter.GetString();
}


template< typename T0, typename T1 >
inline std::string Format( const std::string& format, const T0& a0, const T1& a1 )
{
    Detail::Formatter formatter( format );
    formatter.Feed( 0, Detail::SprintfParameter< T0 >()( a0 ));
    formatter.Feed( 1, Detail::SprintfParameter< T1 >()( a1 ));
    return formatter.GetString();
}


template< typename T0, typename T1, typename T2 >
inline std::string Format(
    const std::string& format, const T0& a0, const T1& a1, const T2& a2 )
{
    Detail::Formatter formatter( format );
    formatter.Feed( 0, Detail::SprintfParameter< T0 >()( a0 ));
    formatter.Feed( 1, Detail::SprintfParameter< T1 >()( a1 ));
    formatter.Feed( 2, Detail::SprintfParameter< T2 >()( a2 ));
    return formatter.GetString();
}


template< typename T0, typename T1, typename T2, typename T3 >
inline std::string Format(
    const std::string& format, const T0& a0, const T1& a1, const T2& a2, const T3& a3 )
{
    Detail::Formatter formatter( format );
    formatter.Feed( 0, Detail::SprintfParameter< T0 >()( a0 ));
    formatter.Feed( 1, Detail::SprintfParameter< T1 >()( a1 ));
    formatter.Feed( 2, Detail::SprintfParameter< T2 >()( a2 ));
    formatter.Feed( 3, Detail::SprintfParameter< T3 >()( a3 ));
    return formatter.GetString();
}


template< typename T0, typename T1, typename T2, typename T3, typename T4 >
inline std::string Format(
    const std::string& format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4 )
{
    Detail::Formatter formatter( format );
    formatter.Feed( 0, Detail::SprintfParameter< T0 >()( a0 ));
    formatter.Feed( 1, Detail::SprintfParameter< T1 >()( a1 ));
    formatter.Feed( 2, Detail::SprintfParameter< T2 >()( a2 ));
    formatter.Feed( 3, Detail::SprintfParameter< T3 >()( a3 ));
    formatter.Feed( 4, Detail::SprintfParameter< T4 >()( a4 ));
    return formatter.GetString();
}

template< typename T0, typename T1, typename T2, typename T3, typename T4, typename T5 >
inline std::string Format(
    const std::string& format, const T0& a0, const T1& a1, const T2& a2, const T3& a3, const T4& a4, const T5& a5 )
{
    Detail::Formatter formatter( format );
    formatter.Feed( 0, Detail::SprintfParameter< T0 >()( a0 ));
    formatter.Feed( 1, Detail::SprintfParameter< T1 >()( a1 ));
    formatter.Feed( 2, Detail::SprintfParameter< T2 >()( a2 ));
    formatter.Feed( 3, Detail::SprintfParameter< T3 >()( a3 ));
    formatter.Feed( 4, Detail::SprintfParameter< T4 >()( a4 ));
	formatter.Feed( 5, Detail::SprintfParameter< T5 >()( a5 ));
    return formatter.GetString();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_FORMAT_H
