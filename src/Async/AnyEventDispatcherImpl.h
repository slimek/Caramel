// Caramel C++ Library - Async Facility - Any Event Dispatcher Private Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_DISPATCHER_IMPL_H
#define __CARAMEL_ASYNC_ANY_EVENT_DISPATCHER_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Async/AnyEventTargetImpl.h"
#include <Caramel/Async/AnyEventDispatcher.h>
#include <Caramel/Concurrent/HashMap.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Dispatcher
//

class AnyEventDispatcherImpl : public AnyEventTargetImpl
{
public:

    /// Targets Management ///

    void LinkTarget( AnyEventTargetPtr&& target );
    void UnlinkTarget( const AnyEventTargetPtr& target );

    Usize GetNumTargets() const { return m_targets.Size(); }


    /// Operations ///

    void Dispatch( const AnyEvent& event );


    /// Implements AnyEventTargetImpl ///

    void Send( const AnyEvent& event, Uint age ) override;


private:

    typedef Concurrent::HashMapWithSnapshot< AnyEventTargetPtr, Uint > TargetMap;
    TargetMap m_targets;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_DISPATCHER_IMPL_H
