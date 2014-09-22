// Caramel C++ Library - Async Facility - Detail - Any Event Dispatcher Front Header

#ifndef __CARAMEL_ASYNC_DETAIL_ANY_EVENT_DISPATCHER_FRONT_H
#define __CARAMEL_ASYNC_DETAIL_ANY_EVENT_DISPATCHER_FRONT_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEventTarget.h>


namespace Caramel
{

// Forwards declaration
class AnyEventDispatcher;
class AnyEventFrontImpl;

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Dispatcher Front
// - A temporary copyable front for AnyEventDispatcher.
//   Can only be created by AnyEventDispatcher::Front().
//
// USAGE:
//
//   AnyEventDispatcherFront is mostly used in a lambda expression. For example:
//
//     void MyModel::LoadFile()
//     {
//         auto front = m_dispatcher.Front();
//         auto task = MakeTask( "Load",
//         [=]
//         {
//             const ByteArray data = InputFile( fileName ).LoadData();
//             front.DispatchEvent( EVENT_FILE_LOADED, data );
//         });
//     }
//
//   Then for some reasons you want to ignore the loading result before the loading completes
//   - suppose it takes a long time :) . What you need to do is just resetting the dispatcher :
//
//     void MyModel::Reset()
//     {
//         m_dispatcher.Reset();
//     }
//
//   In this case, the file is still loaded, and an event is post. But since the host dispatcher
//   has been unlinked from its front, the event goes nowhere and would be ignored.
// 

class AnyEventDispatcherFront
{
    friend class Caramel::AnyEventDispatcher;

public:

    //
    // Dispatch Events to host Dispatcher
    // - Since this front just pass events to its host,
    //   it's fine to treat these functions as 'const'.
    //

    void Dispatch( const AnyEvent& event ) const;

    void DispatchEvent( Int eventId ) const;
    void DispatchEvent( Int eventId, const Any& value ) const;
    void DispatchEvent( Int eventId, Any&& value ) const;


private:

    explicit AnyEventDispatcherFront( AnyEventTargetPtr hostDispatcher );

    std::shared_ptr< AnyEventFrontImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ASYNC_DETAIL_ANY_EVENT_DISPATCHER_FRONT_H
