// Caramel C++ Library - Thread Facility - Mutex Locks Header

#ifndef __CARAMEL_THREAD_MUTEX_LOCKS_H
#define __CARAMEL_THREAD_MUTEX_LOCKS_H
#pragma once

#include <Caramel/Caramel.h>
#include <mutex>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Lock Functions
//

template< typename MutexType >
std::unique_lock< MutexType > UniqueLock( MutexType& mutex )
{
    return std::unique_lock< MutexType >( mutex );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_MUTEX_LOCKS_H
