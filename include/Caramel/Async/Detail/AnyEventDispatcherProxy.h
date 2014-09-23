// Caramel C++ Library - Async Facility - Detail - Any Event Dispatcher Proxy Header

#ifndef __CARAMEL_ASYNC_DETAIL_ANY_EVENT_DISPATCHER_PROXY_H
#define __CARAMEL_ASYNC_DETAIL_ANY_EVENT_DISPATCHER_PROXY_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEventTarget.h>


namespace Caramel
{

// Forwards declaration
class AnyEventDispatcher;
class AnyEventTargetProxyImpl;

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Dispatcher Proxy
// - A temporary copyable proxy for AnyEventDispatcher.
//   Can only be created by AnyEventDispatcher::Proxy().
//
// USAGE:
//
//   AnyEventDispatcherProxy is mostly used in a lambda expression. For example:
//
//     void MyModel::LoadFile()
//     {
//         auto disp = m_dispatcher.Proxy();
//         auto task = MakeTask( "Load",
//         [=]
//         {
//             const ByteArray data = InputFile( fileName ).LoadData();
//             disp.DispatchEvent( EVENT_FILE_LOADED, data );
//         });
//     }
//
//   Then for some reasons you want to ignore the loading result before the loading completes
//   -- suppose it takes a long time :) -- What you need to do is just resetting the dispatcher :
//
//     void MyModel::Reset()
//     {
//         m_dispatcher.Reset();
//     }
//
//   In this case, the file is still loaded, and an event is post. But since the host dispatcher
//   has been unlinked from its proxy, the event goes nowhere and would be ignored.
// 

class AnyEventDispatcherProxy : public AnyEventTarget
{
    friend class Caramel::AnyEventDispatcher;

public:

    //
    // Dispatch Events to host Dispatcher
    // - Since this proxy just pass events to its host,
    //   it's fine to treat these functions as 'const'.
    //

    void Dispatch( const AnyEvent& event ) const;

    void DispatchEvent( Int eventId ) const;
    void DispatchEvent( Int eventId, const Any& value ) const;
    void DispatchEvent( Int eventId, Any&& value ) const;

    
    /// AnyEventTarget operations ///

    // Unlink from all linked dispatchers.
    // Proxy doesn't cache events, therefore there is nothing to discard.
    // But you CAN still use this proxy to send events to its host.
    void Reset() override;


private:

    explicit AnyEventDispatcherProxy( AnyEventTargetPtr hostDispatcher );

    AnyEventTargetPtr GetTargetImpl() const override;

    std::shared_ptr< AnyEventTargetProxyImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ASYNC_DETAIL_ANY_EVENT_DISPATCHER_PROXY_H
