// Caramel C++ Library - Object Facility - Singleton Header

#ifndef __CARAMEL_OBJECT_SINGLETON_H
#define __CARAMEL_OBJECT_SINGLETON_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Singleton
//

template< typename T, Uint longevity = 0 >
class Singleton
{
public:
    static T* Instance();
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_OBJECT_SINGLETON_H
