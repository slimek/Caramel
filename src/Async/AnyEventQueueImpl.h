// Caramel C++ Library - Async Facility - Any Event Queue Private Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_QUEUE_IMPL_H
#define __CARAMEL_ASYNC_ANY_EVENT_QUEUE_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Async/AnyEventTargetImpl.h"
#include <Caramel/Async/AnyEventQueue.h>
#include <Caramel/Concurrent/IntervalSet.h>
#include <Caramel/Concurrent/Queue.h>


namespace Caramel
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

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_QUEUE_IMPL_H
