// Caramel C++ Library - Async Amenity - Any Event Queue Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_QUEUE_H
#define __CARAMEL_ASYNC_ANY_EVENT_QUEUE_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Async/AnyEventTarget.h>
#include <Caramel/Async/Detail/AnyEventQueueImpl.h>
#include <boost/noncopyable.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Queue
//

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
    void Reset();


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

    Detail::AnyEventTargetPtr GetTargetImpl() const override { return m_impl; }


    std::shared_ptr< Detail::AnyEventQueueImpl > m_impl;

};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline AnyEventQueue::AnyEventQueue()
    : m_impl( new Detail::AnyEventQueueImpl )
{
}


inline AnyEventQueue::~AnyEventQueue()
{
    m_impl->Destroy();
}


//
// Operations
//

inline void AnyEventQueue::Push( const AnyEvent& evt )
{
    m_impl->Push( evt );
}


inline void AnyEventQueue::Push( AnyEvent&& evt )
{
    m_impl->Push( std::move( evt ));
}


inline void AnyEventQueue::PushEvent( Int eventId )
{
    m_impl->Push( AnyEvent( eventId ));
}


inline void AnyEventQueue::PushEvent( Int eventId, const Any& any )
{
    m_impl->Push( AnyEvent( eventId, any ));
}


inline void AnyEventQueue::PushEvent( Int eventId, Any&& any )
{
    m_impl->Push( AnyEvent( eventId, std::move( any )));
}


inline Bool AnyEventQueue::TryPop( AnyEvent& evt )
{
    return m_impl->TryPop( evt );
}


inline void AnyEventQueue::Reset()
{
    // Create a new impl before destroy the old impl,
    // to prevent the address is the same with the former.

    auto oldImpl = m_impl;
    m_impl = std::make_shared< Detail::AnyEventQueueImpl >();
    oldImpl->Destroy();
}


//
// To Prevent Ambiguous IDs
//

inline Bool AnyEventQueue::RegisterIdRange( Int minEventId, Int maxEventId )
{
    return m_impl->RegisterIdRange( minEventId, maxEventId );
}


inline void AnyEventQueue::UnregisterIdRange( Int minEventId, Int maxEventId )
{
    m_impl->UnregisterIdRange( minEventId, maxEventId );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_QUEUE_H

