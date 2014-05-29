// Caramel C++ Library - Async Facility - Any Event Queue Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_QUEUE_H
#define __CARAMEL_ASYNC_ANY_EVENT_QUEUE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEventTarget.h>
#include <boost/noncopyable.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Queue
//

class AnyEventQueueImpl;

class AnyEventQueue : public AnyEventTarget
                    , public boost::noncopyable
{
public:
    
    AnyEventQueue();
    ~AnyEventQueue();


    /// Operations ///

    void Push( const AnyEvent& evt );
    void Push( AnyEvent&& evt );

    // Make an AnyEvent inside the function.
    void PushEvent( Int eventId );
    void PushEvent( Int eventId, const Any& any );
    void PushEvent( Int eventId, Any&& any );

    Bool TryPop( AnyEvent& evt );
    

    // This function has two effects:
    // 1. Unlink from all linked dispatchers.
    // 2. Discard all unprocessed events.
    void UnlinkAll();


    //
    // To Prevent Ambiguous IDs
    // - Only check IDs when registering, not when each pushing.
    //   Cooperate with AnyEventDispatcher.
    //

    // Returns false if the ID range overlaps with others.
    Bool RegisterIdRange( Int minEventId, Int maxEventId );

    void UnregisterIdRange( Int minEventId, Int maxEventId );


private:

    /// Implements AnyEventTarget ///

    AnyEventTargetPtr GetTargetImpl() const override;


    /// Data Members ///

    std::shared_ptr< AnyEventQueueImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_QUEUE_H

