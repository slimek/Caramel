// Caramel C++ Library - Async Facility - Detail - Any Event Queue Proxy Header

#ifndef __CARAMEL_ASYNC_DETAIL_ANY_EVENT_QUEUE_PROYX_H
#define __CARAMEL_ASYNC_DETAIL_ANY_EVENT_QUEUE_PROYX_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEventTarget.h>

namespace Caramel
{

// Forwards declaration
class AnyEventQueue;
class AnyEventTargetProxyImpl;

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Queue Proxy
// - A tempoarary copyable proxy for AnyEventQueue.
//   Can only be created by AnyEventQueue::Proxy().
//
// USGAE:
//
//   AnyEventQueueProxy is mostly used in a lambda expression. For example:
//
//     void MyModel::LoadFile()
//     {
//         auto queue = m_queue.Proxy();
//         auto task = MakeTask( "Load",
//         [=]
//         {
//             const ByteArray data = InputFile( fileName ).LoadData();
//             queue.PushEvent( EVENT_FILE_LOADED, data );
//         });
//     }
//
//   Then for some reasons you want to ignore the loading result before the loading completes
//   -- suppose it takes a long time :) -- What you need to do is just resetting the queue :
//
//     void MyModel::Reset()
//     {
//         m_queue.Reset();
//     }
//
//   In this case, the file is still loaded, and an event is pushed. But since the host queue
//   has been unlinked from its proxy, the event goes nowhere and would be ignored.
// 

class AnyEventQueueProxy : public AnyEventTarget
{
    friend class Caramel::AnyEventQueue;

public:
    
    void Push( const AnyEvent& event ) const;

    void PushEvent( Int eventId ) const;
    void PushEvent( Int eventId, const Any& value ) const;
    void PushEvent( Int eventId, Any&& value ) const;


    /// AnyEventTarget operations ///

    // Unlink from all linked dispatchers.
    // Proxy doesn't cache events, therefore there is nothing to discard.
    // But you CAN still use this proxy to send events to its host.
    void Reset() override;


private:

    explicit AnyEventQueueProxy( AnyEventTargetPtr hostQueue );

    AnyEventTargetPtr GetTargetImpl() const override;

    std::shared_ptr< AnyEventTargetProxyImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ASYNC_DETAIL_ANY_EVENT_QUEUE_PROYX_H
