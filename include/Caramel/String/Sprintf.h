// Caramel C++ Library - String Facility - Sprintf Header

#ifndef __CARAMEL_STRING_SPRINTF_H
#define __CARAMEL_STRING_SPRINTF_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
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


//
// Sprintf Functions Variadic Templates
//

#include <Caramel/String/Inline/Sprintf_Sprintf.h>


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel


#endif // __CARAMEL_STRING_SPRINTF_H

