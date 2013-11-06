// Caramel C++ Library - Thread Facility - Spin Mutex Header

#ifndef __CARAMEL_THREAD_SPIN_MUTEX_H
#define __CARAMEL_THREAD_SPIN_MUTEX_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <boost/noncopyable.hpp>
#include <boost/smart_ptr/detail/spinlock_pool.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Spin Mutex
// - This is a wrapper of Boost.SmartPtr spinlock.
//

class SpinMutex : public boost::noncopyable
{
public:

    class ScopedLock : public boost::noncopyable
    {
    public:
        ScopedLock( SpinMutex& mutex );
        ~ScopedLock();

    private:
        boost::detail::spinlock& m_lock;
    };
};


//
// Implementation
//

inline SpinMutex::ScopedLock::ScopedLock( SpinMutex& mutex )
    : m_lock( boost::detail::spinlock_pool< 0 >::spinlock_for( &mutex ))
{
    m_lock.lock();
}


inline SpinMutex::ScopedLock::~ScopedLock()
{
    m_lock.unlock();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_SPIN_MUTEX_H
