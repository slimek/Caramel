// Caramel C++ Library - Thread Facility - Mutex Header

#ifndef __CARAMEL_THREAD_MUTEX_H
#define __CARAMEL_THREAD_MUTEX_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <mutex>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Mutex
// - A recursive Mutex
//

class Mutex : public std::recursive_mutex
{
public:

    typedef std::unique_lock< std::recursive_mutex > UniqueLock;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_MUTEX_H
