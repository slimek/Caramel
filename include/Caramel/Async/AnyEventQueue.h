// Caramel C++ Library - Async Amenity - Any Event Queue Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_QUEUE_H
#define __CARAMEL_ASYNC_ANY_EVENT_QUEUE_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Async/AnyEvent.h>
#include <Caramel/Concurrent/IntervalSet.h>
#include <Caramel/Concurrent/Queue.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Queue
//

class AnyEventQueue
{
public:

    /// Operations ///

    void Push( const AnyEvent& evt );
    void Push( AnyEvent&& evt );

    // Make an AnyEvent inside the function.
    void PushEvent( Int eventId );
    void PushEvent( Int eventId, const Any& any );
    void PushEvent( Int eventId, Any&& any );

    Bool TryPop( AnyEvent& evt );
    

    //
    // To Prevent Ambiguous IDs
    // - Only check IDs when registering, not when each pushing.
    //   Cooperate with AnyEventDispatcher.
    //

    // Returns false if the ID range overlaps with others.
    Bool RegisterIdRange( Int minEventId, Int maxEventId );

    void UnregisterIdRange( Int minEventId, Int maxEventId );


private:

    /// Data Members ///

    typedef Concurrent::Queue< AnyEvent > EventQueue;
    EventQueue m_events;

    typedef Concurrent::IntervalSet< Int > EventIdRangeSet;
    EventIdRangeSet m_registeredIdRanges;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline void AnyEventQueue::Push( const AnyEvent& evt )
{
    m_events.Push( evt );
}


inline void AnyEventQueue::Push( AnyEvent&& evt )
{
    m_events.Push( std::move( evt ));
}


inline void AnyEventQueue::PushEvent( Int eventId )
{
    m_events.Push( AnyEvent( eventId ));
}


inline void AnyEventQueue::PushEvent( Int eventId, const Any& any )
{
    m_events.Push( AnyEvent( eventId, any ));
}


inline void AnyEventQueue::PushEvent( Int eventId, Any&& any )
{
    m_events.Push( AnyEvent( eventId, std::move( any )));
}


inline Bool AnyEventQueue::TryPop( AnyEvent& evt )
{
    return m_events.TryPop( evt );
}


//
// To Prevent Ambiguous IDs
//

inline Bool AnyEventQueue::RegisterIdRange( Int minEventId, Int maxEventId )
{
    return m_registeredIdRanges.InsertClosed( minEventId, maxEventId );
}


inline void AnyEventQueue::UnregisterIdRange( Int minEventId, Int maxEventId )
{
    m_registeredIdRanges.EraseClosed( minEventId, maxEventId );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_QUEUE_H

