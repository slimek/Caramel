// Caramel C++ Library - String Facility - Sprintf Header

#ifndef __CARAMEL_STRING_SPRINTF_H
#define __CARAMEL_STRING_SPRINTF_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/String/Detail/SprintfParameter.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Sprintf Functions
//

namespace Detail
{

std::string SprintfImpl( const Char* format, ... );

} // namespace Detail


/// Functions with no Arguments ///

inline std::string Sprintf( const Char* format )
{
    return std::string( format );
}


inline const std::string& Sprintf( const std::string& format )
{
    return format;
}


/// Functions with 1 Argument ///

template< typename T0 >
inline std::string Sprintf( const Char* format, const T0& a0 )
{
    return Detail::SprintfImpl( format, Detail::SprintfParameter< T0 >()( a0 ));
}


template< typename T0 >
inline std::string Sprintf( const std::string& format, const T0& a0 )
{
    return Detail::SprintfImpl( format.c_str(), Detail::SprintfParameter< T0 >()( a0 ));
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel


#endif // __CARAMEL_STRING_SPRINTF_H

