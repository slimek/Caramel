// Caramel C++ Library - Thread Facility - Spin Mutex Header

#ifndef __CARAMEL_THREAD_SPIN_MUTEX_H
#define __CARAMEL_THREAD_SPIN_MUTEX_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <boost/noncopyable.hpp>
#include <boost/smart_ptr/detail/spinlock.hpp>


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
    SpinMutex();

    class ScopedLock;
    friend class ScopedLock;

    class ScopedLock : public boost::detail::spinlock::scoped_lock
    {
        typedef boost::detail::spinlock::scoped_lock Inherited;
    public:
        explicit ScopedLock( SpinMutex& mutex );
    };

private:
    boost::detail::spinlock m_mutex;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline SpinMutex::SpinMutex()
    : m_mutex( BOOST_DETAIL_SPINLOCK_INIT )
{}


inline SpinMutex::ScopedLock::ScopedLock( SpinMutex& mutex )
    : Inherited( mutex.m_mutex )
{}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_SPIN_MUTEX_H
