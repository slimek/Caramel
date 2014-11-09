// Caramel C++ Library - Async Facility - Any Event Poller Private Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_POLLER_IMPL_H
#define __CARAMEL_ASYNC_ANY_EVENT_POLLER_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEventPoller.h>
#include <Caramel/Concurrent/Queue.h>
#include <Caramel/Thread/MutexLocks.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Poller
//

class AnyEventPollerImpl
{
public:

    struct Entry
    {
        AnyEvent event;
        std::function< void( const AnyEvent& ) > handler;
    };

    void Emit( Entry&& entry, Uint age );

    void PollOne();

    void Clear();


    /// Reference Aging ///

    void IncrementAge();

    // The lock is not locked if the age doesn't equal.    
    UniqueLock CompareAge( Uint age ) const;
    
    Uint GetAge() const { return m_age; }


private:
    
    typedef Concurrent::Queue< Entry > EntryQueue;
    EntryQueue m_entries;

    Uint m_age;
    mutable std::mutex m_ageMutex;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_POLLER_IMPL_H
