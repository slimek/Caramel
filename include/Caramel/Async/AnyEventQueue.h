// Caramel C++ Library - Async Amenity - Any Event Queue Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_QUEUE_H
#define __CARAMEL_ASYNC_ANY_EVENT_QUEUE_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Async/AnyEvent.h>
#include <Caramel/Concurrent/IntervalSet.h>
#include <Caramel/Concurrent/Queue.h>
#include <Caramel/Error/Alert.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Queue
//

class AnyEventQueue
{
public:
    
    class PushPort;
    friend class PushPort;


    /// Operations ///

    PushPort Register( const std::string& name, Int minEventId, Int maxEventId );

    Bool TryPop( AnyEvent& evt );


private:

    /// Functions for PushPort ///

    void Push( AnyEvent&& evt );

    void Unregister( Int minEventId, Int maxEventId );


    /// Data Members ///

    typedef Concurrent::IntervalSet< Int > EventIdRangeSet;
    EventIdRangeSet m_eventIdRanges;

    typedef Concurrent::Queue< AnyEvent > EventQueue;
    EventQueue m_events;
};


class AnyEventQueue::PushPort
{
public:

    PushPort( AnyEventQueue& host, const std::string& name, Int minEventId, Int maxEventId );

    void PushEvent( Int eventId, const Any& value );
    void PushEvent( Int eventId, Any&& value );


private:

    void Release();

    AnyEventQueue& m_host;
    std::string m_name;
    Int m_minEventId;
    Int m_maxEventId;

    std::shared_ptr< EmptyType > m_releaser;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline AnyEventQueue::PushPort AnyEventQueue::Register( const std::string& name, Int minEventId, Int maxEventId )
{
    if ( ! m_eventIdRanges.InsertClosed( minEventId, maxEventId ))
    {
        CARAMEL_ALERT( "Event id overlapped, name: %s, min: %d, max: %d", name, minEventId, maxEventId );
    }

    return PushPort( *this, name, minEventId, maxEventId );
}


inline void AnyEventQueue::Unregister( Int minEventId, Int maxEventId )
{
    m_eventIdRanges.EraseClosed( minEventId, maxEventId );
}


inline void AnyEventQueue::Push( AnyEvent&& evt )
{
    m_events.Push( evt );
}


inline Bool AnyEventQueue::TryPop( AnyEvent& evt )
{
    return m_events.TryPop( evt );
}


//
// Push Port
//

inline AnyEventQueue::PushPort::PushPort(
    AnyEventQueue& host, const std::string& name, Int minEventId, Int maxEventId )
    : m_host( host )
    , m_name( name )
    , m_minEventId( minEventId )
    , m_maxEventId( maxEventId )
{
    m_releaser.reset( new EmptyType, [=] ( EmptyType* ) { this->Release(); } );
}


inline void AnyEventQueue::PushPort::PushEvent( Int eventId, const Any& value )
{
    m_host.Push( AnyEvent( eventId, value ));
}


inline void AnyEventQueue::PushPort::PushEvent( Int eventId, Any&& value )
{
    m_host.Push( AnyEvent( eventId, value ));
}


inline void AnyEventQueue::PushPort::Release()
{
    m_host.Unregister( m_minEventId, m_maxEventId );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_QUEUE_H

