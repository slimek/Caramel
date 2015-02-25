// Caramel C++ Library - Async Facility - Any Event Dispatcher Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_DISPATCHER_H
#define __CARAMEL_ASYNC_ANY_EVENT_DISPATCHER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/Detail/AnyEventDispatcherProxy.h>
#include <Caramel/Async/AnyEventTarget.h>
#include <boost/noncopyable.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Dispatcher
//

class AnyEventDispatcherImpl;

class AnyEventDispatcher : public AnyEventTarget
                         , public boost::noncopyable
{
public:

    AnyEventDispatcher();
    ~AnyEventDispatcher();


    /// Targets Management ///

    void LinkTarget( AnyEventTarget& target );
    void UnlinkTarget( AnyEventTarget& target );

    Usize GetNumTargets() const;


    /// Dispatch Events to Targets ///

    void Dispatch( const AnyEvent& event );

    void DispatchEvent( Int eventId );
    void DispatchEvent( Int eventId, const Any& value );
    void DispatchEvent( Int eventId, Any&& value );


    //
    // Create a temporary dispatcher proxy.
    // - See AnyEventDispatcherProxy.h for its usage.
    //
    Detail::AnyEventDispatcherProxy Proxy();


    /// AnyEventTarget Operations ///

    // Unlink from all linked dispatchers. Usually you call this to unlink from all proxies.
    // Dispatcher doesn't cache events, therefore there is nothing to discard.
    void Reset() override;


private:

    /// Implements AnyEventTarget ///

    AnyEventTargetPtr GetTargetImpl() const override;


    /// Data Members ///

    std::shared_ptr< AnyEventDispatcherImpl > m_impl;          
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_DISPATCHER_H
