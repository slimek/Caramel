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
class AnyEventDispatcherImpl;

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
//   And for some reasons you want to ignore the loading result. Just reset the dispatcher :
//
//     void MyModel::Reset()
//     {
//         m_dispatcher.Reset();
//     }
//
//   In this case, the file is still loaded, and an event is post. But the host dispatcher
//   has been unlinked from is front, therefore the event would be ignored.
// 

class AnyEventDispatcherFront
{
    friend class AnyEventDispatcher;

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

    std::shared_ptr< AnyEventDispatcherImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ASYNC_DETAIL_ANY_EVENT_DISPATCHER_FRONT_H
