// Caramel C++ Library - Metaprogramming Amenity - Select Header

#ifndef __CARAMEL_META_SELECT_H
#define __CARAMEL_META_SELECT_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Select Type
// - Similar with std::conditional, but can be used recursively.
//

/// Primary Template ///

template< Bool condition, typename T0, typename T1 > struct SelectT;


/// Condition is True ///

template< typename T0, typename T1 >
struct SelectT< true, T0, T1 >
{
    typedef T0 Type;
};


/// Condition is False ///

template< typename T0, typename T1 >
struct SelectT< false, T0, T1 >
{
    typedef T1 Type;
};


/// Recursive ///

template< Bool cond1, typename T0, typename T1, typename T2 >
struct SelectT< false, T0, SelectT< cond1, T1, T2 > >
{
    typedef typename SelectT< cond1, T1, T2 >::Type Type;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_META_SELECT_H
