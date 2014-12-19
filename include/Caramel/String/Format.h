// Caramel C++ Library - String Facility - Format Header

#ifndef __CARAMEL_STRING_FORMAT_H
#define __CARAMEL_STRING_FORMAT_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/String/Detail/Formatter.h>
#include <Caramel/String/Detail/FormatRecursive.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Format Functions
//

// With Variadic Arguments

template< typename... Args >
inline std::string Format( const std::string& format, Args&&... args )
{
    Detail::Formatter formatter( format );
    return Detail::FormatRecursive( formatter, std::forward< Args >( args )... );
}


// With no Arguments

inline std::string Format( const std::string& format )
{
    Detail::Formatter formatter( format );
    return formatter.GetString();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_STRING_FORMAT_H
