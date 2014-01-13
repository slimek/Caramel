// Caramel C++ Library - Async Amenity - Any Event Dispatcher Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_DISPATCHER_H
#define __CARAMEL_ASYNC_ANY_EVENT_DISPATCHER_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Async/AnyEvent.h>
#include <Caramel/Async/AnyEventQueue.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Dispatcher
//

class AnyEventDispatcher
{
public:

    AnyEventDispatcher( const std::string& name, Int minEventId, Int maxEventId );


    /// Register Queues ///

    void RegisterQueue( AnyEventQueue& queue );
    void UnregisterQueue( AnyEventQueue& queue );


    /// Dispatch Events to Queues ///

    void DispatchEvent( Int eventId, const Any& value );
    void DispatchEvent( Int eventId, Any&& value );

    void DispatchEvent( const AnyEvent& evt );


private:

    /// Data Members ///

    std::string m_name;
    Int m_minEventId;
    Int m_maxEventId;
    
            
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

void AnyEventDispatcher::DispatchEvent( Int eventId, const Any& value )
{
    this->DispatchEvent( AnyEvent( eventId, value ));
}


void AnyEventDispatcher::DispatchEvent( Int eventId, Any&& value )
{
    this->DispatchEvent( AnyEvent( eventId, value ));
}


void AnyEventDispatcher::DispatchEvent( const AnyEvent& evt )
{
    ; // TODO ...
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_DISPATCHER_H
