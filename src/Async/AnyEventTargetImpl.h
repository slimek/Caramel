// Caramel C++ Library - Async Facility - Any Event Target Private Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_TARGET_IMPL_H
#define __CARAMEL_ASYNC_ANY_EVENT_TARGET_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEvent.h>
#include <Caramel/Thread/MutexLocks.h>
#include <mutex>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Target
//

class AnyEventTargetImpl
{
public:

    AnyEventTargetImpl();
    virtual ~AnyEventTargetImpl() {}

    virtual void Send( const AnyEvent& evt, Uint age ) = 0;


    /// Target Destroyed ///

    // The owner should call this function in destructor.
    // - ATTENTION: If the owner is copyable, you may need additional reference counting.
    void Destroy();

    Bool IsDestroyed() const { return m_destroyed; }


    /// Reference Aging ///

    void IncrementAge();
    
    // The lock is not locked if the age doesn't equal.    
    UniqueLock CompareAge( Uint age ) const;
    
    Uint GetAge() const { return m_age; }


private:

    Bool m_destroyed;
    
    Uint m_age;
    mutable std::mutex m_ageMutex;
};

typedef std::shared_ptr< AnyEventTargetImpl > AnyEventTargetPtr;


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_TARGET_IMPL_H
