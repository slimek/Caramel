// Caramel C++ Library - Async Amenity - Detail - Any Event Queue Private Header

#ifndef __CARAMEL_ASYNC_DETAIL_ANY_EVENT_QUEUE_IMPL_H
#define __CARAMEL_ASYNC_DETAIL_ANY_EVENT_QUEUE_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/Detail/AnyEventTargetImpl.h>
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

class AnyEventQueueImpl : public Concurrent::Queue< AnyEvent >
                        , public AnyEventTargetImpl
{
public:

    //
    // To Prevent Ambiguous IDs
    // - Only check IDs when registering, not when each pushing.
    //   Cooperate with AnyEventDispatcher.
    //

    // Returns false if the ID range overlaps with others.
    Bool RegisterIdRange( Int minEventId, Int maxEventId );

    void UnregisterIdRange( Int minEventId, Int maxEventId );


    /// Implements AnyEventTargetImpl ///

    void Send( const AnyEvent& evt, Uint age ) override;


private:

    /// Data Members ///

    typedef Concurrent::IntervalSet< Int > EventIdRangeSet;
    EventIdRangeSet m_registeredIdRanges;

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline void AnyEventQueueImpl::Send( const AnyEvent& evt, Uint age )
{
    UniqueLock ulock = this->CompareAge( age );
    if ( ulock )
    {
        this->Push( evt );
    }
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
