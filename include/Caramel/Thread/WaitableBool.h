// Caramel C++ Library - Thread Facility - Waitable Bool Header

#ifndef __CARAMEL_THREAD_WAITABLE_BOOL_H
#define __CARAMEL_THREAD_WAITABLE_BOOL_H
#pragma once

#include <Caramel/Caramel.h>
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
    Bool oldValue = false;

    {
        auto ulock = UniqueLock( m_mutex );
        oldValue = m_value;
        m_value = value;
    }

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
    auto ulock = UniqueLock( m_mutex );

    while ( ! m_value )
    {
        m_becomesTrue.wait( ulock );
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_THREAD_WAITABLE_BOOL_H
