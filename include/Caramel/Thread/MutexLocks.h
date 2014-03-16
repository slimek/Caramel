// Caramel C++ Library - Thread Facility - Mutex Locks Header

#ifndef __CARAMEL_THREAD_MUTEX_LOCKS_H
#define __CARAMEL_THREAD_MUTEX_LOCKS_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <mutex>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Lock Classes
//

//
// Lock Guard
// - The default lock. Use it as possible.
//
typedef std::lock_guard< std::mutex > LockGuard;


//
// Unique Lock
// - More flexible. It can be deferred, try to lock with timeout, etc.
//   It also can cooperate with std::condition_variable.
//
//   But DO NOT use it unless it is neccesary.
//
typedef std::unique_lock< std::mutex > UniqueLock;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_MUTEX_LOCKS_H
