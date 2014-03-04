// Caramel C++ Library - Metaprogramming Amenity - Is General String Header

#ifndef __CARAMEL_META_IS_GENERAL_STRING_H
#define __CARAMEL_META_IS_GENERAL_STRING_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Meta/Utility.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Is General String
// - True if T is :
//   std::string
//   C-style string - char* and char[].
//

template< typename T >
struct IsGeneralStringT
    : public BoolType
        <
            std::is_same< Char*,       typename std::decay< T >::type >::value
         || std::is_same< const Char*, typename std::decay< T >::type >::value
        >
{};


template<>
struct IsGeneralStringT< std::string > : public TrueType
{};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_META_IS_GENERAL_STRING_H
