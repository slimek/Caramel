// Caramel C++ Library - Async Facility - Detail - Any Event Queue Front Header

#ifndef __CARAMEL_ASYNC_DETAIL_ANY_EVENT_QUEUE_FRONT_H
#define __CARAMEL_ASYNC_DETAIL_ANY_EVENT_QUEUE_FRONT_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEventTarget.h>

namespace Caramel
{

// Forwards declaration
class AnyEventQueue;
class AnyEventFrontImpl;

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Queue Front
// - A tempoarary copyable front for AnyEventQueue.
//   Can only be created by AnyEventQueue::Front().
//
// USGAE:
//
//   AnyEventQueueFront is mostly used in a lambda expression. For example:
//
//     void MyModel::LoadFile()
//     {
//         auto front = m_queue.Front();
//         auto task = MakeTask( "Load",
//         [=]
//         {
//             const ByteArray data = InputFile( fileName ).LoadData();
//             front.PushEvent( EVENT_FILE_LOADED, data );
//         });
//     }
//
//   Then for some reasons you want to ignore the loading result before the loading completes
//   - suppose it takes a long time :) . What you need to do is just resetting the queue :
//
//     void MyModel::Reset()
//     {
//         m_queue.Reset();
//     }
//
//   In this case, the file is still loaded, and an event is post. But since the host queue
//   has been unlinked from its front, the event goes nowhere and would be ignored.
// 

class AnyEventQueueFront
{
    friend class Caramel::AnyEventQueue;

public:
    
    void Push( const AnyEvent& event ) const;

    void PushEvent( Int eventId ) const;
    void PushEvent( Int eventId, const Any& value ) const;
    void PushEvent( Int eventId, Any&& value ) const;

private:

    explicit AnyEventQueueFront( AnyEventTargetPtr hostQueue );

    std::shared_ptr< AnyEventFrontImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ASYNC_DETAIL_ANY_EVENT_QUEUE_FRONT_H
