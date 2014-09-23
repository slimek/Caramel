// Caramel C++ Library - Async Facility - Any Event Target Proxy Private Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_TARGET_PROXY_IMPL_H
#define __CARAMEL_ASYNC_ANY_EVENT_TARGET_PROXY_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Async/AnyEventTargetImpl.h"


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Target Proxy
//

class AnyEventTargetProxyImpl : public AnyEventTargetImpl
{
public:

    explicit AnyEventTargetProxyImpl( AnyEventTargetPtr hostTarget );

    void SendToHost( const AnyEvent& event );

    /// Implements AnyEventTargetImpl ///

    void Send( const AnyEvent& event, Uint age ) override;

private:

    AnyEventTargetPtr m_hostTarget;
    Uint m_hostAge { 0 };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_TARGET_PROXY_IMPL_H
