// Caramel C++ Library - Metaprogramming Amenity - Utility Header

#ifndef __CARAMEL_META_UTILITY_H
#define __CARAMEL_META_UTILITY_H
#pragma once

#include <Caramel/Caramel.h>
#include <type_traits>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Type of Specified Size
//

template< Uint size >
struct SizerN
{
    Char dummy[size];
};


///////////////////////////////////////////////////////////////////////////////
//
// Make of Type
// - This is a strawman function returns an instance of a type.
//

template< typename T > T MakeT();


///////////////////////////////////////////////////////////////////////////////
//
// Boolean Types
//

struct TrueType  : public std::true_type  { static const Bool VALUE = true; };
struct FalseType : public std::false_type { static const Bool VALUE = false; };

template< Bool expr > struct BoolType;

template<> struct BoolType< true >  : public TrueType {};
template<> struct BoolType< false > : public FalseType {};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_META_UTILITY_H
