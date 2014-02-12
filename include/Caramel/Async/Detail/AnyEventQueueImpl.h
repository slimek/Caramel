// Caramel C++ Library - Async Amenity - Any Event Queue Impl Header

#ifndef __CARAMEL_ASYNC_DETAIL_ANY_EVENT_QUEUE_IMPL_H
#define __CARAMEL_ASYNC_DETAIL_ANY_EVENT_QUEUE_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Async/AnyEvent.h>
#include <Caramel/Concurrent/IntervalSet.h>
#include <Caramel/Concurrent/Queue.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Queue
//

class AnyEventQueueImpl
{
public:

    /// Operations ///

    void Push( const AnyEvent& evt );
    void Push( AnyEvent&& evt );

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

inline void AnyEventQueueImpl::Push( const AnyEvent& evt )
{
    m_events.Push( evt );
}


inline void AnyEventQueueImpl::Push( AnyEvent&& evt )
{
    m_events.Push( std::move( evt ));
}


inline Bool AnyEventQueueImpl::TryPop( AnyEvent& evt )
{
    return m_events.TryPop( evt );
}


//
// To Prevent Ambiguous IDs
//

inline Bool AnyEventQueueImpl::RegisterIdRange( Int minEventId, Int maxEventId )
{
    return m_registeredIdRanges.InsertClosed( minEventId, maxEventId );
}


inline void AnyEventQueueImpl::UnregisterIdRange( Int minEventId, Int maxEventId )
{
    m_registeredIdRanges.EraseClosed( minEventId, maxEventId );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ASYNC_DETAIL_ANY_EVENT_QUEUE_IMPL_H
