// Caramel C++ Library - Value Facility - Plain Types Header

#ifndef __CARAMEL_VALUE_PLAIN_TYPES_H
#define __CARAMEL_VALUE_PLAIN_TYPES_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Plain Pair
//

template< typename T1, typename T2 >
struct PlainPair
{
    T1 first;
    T2 second;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_VALUE_PLAIN_TYPES_H
