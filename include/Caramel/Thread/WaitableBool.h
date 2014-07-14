// Caramel C++ Library - Thread Facility - Waitable Bool Header

#ifndef __CARAMEL_THREAD_WAITABLE_BOOL_H
#define __CARAMEL_THREAD_WAITABLE_BOOL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Thread/MutexLocks.h>
#include <condition_variable>
#include <mutex>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Waitable Bool
// - Block a thread until this boolean becomes true.
//

class WaitableBool
{
public:

    WaitableBool();
    explicit WaitableBool( Bool initialValue );

    
    /// Operators ///

    WaitableBool& operator=( Bool value );


    /// Accessors ///

    operator Bool() const { return m_value; }


    /// Manipulators ///

    void Wait();

    // Return:
    // - true if the value becomes true,
    //   false if it timeouts.    
    Bool WaitFor( const Ticks& timeout );


private:

    Bool m_value;

    std::mutex m_mutex;
    std::condition_variable m_becomesTrue;
};


//
// Implementation
//

inline WaitableBool::WaitableBool()
    : m_value( false )
{
}


inline WaitableBool::WaitableBool( Bool initialValue )
    : m_value( initialValue )
{
}


/// Operators ///

inline WaitableBool& WaitableBool::operator=( Bool value )
{
    LockGuard lock( m_mutex );

    const Bool oldValue = m_value;
    m_value = value;

    if ( ! oldValue && value )
    {
        // false => true
        m_becomesTrue.notify_all();
    }

    return *this;
}


/// Manipulators ///

inline void WaitableBool::Wait()
{
    UniqueLock ulock( m_mutex );

    while ( ! m_value )
    {
        m_becomesTrue.wait( ulock );
    }
}


inline Bool WaitableBool::WaitFor( const Ticks& timeout )
{
    UniqueLock ulock( m_mutex );

    if ( ! m_value )
    {
        m_becomesTrue.wait_for( ulock, timeout.ToStdDuration() );
    }

    return m_value;
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_WAITABLE_BOOL_H
