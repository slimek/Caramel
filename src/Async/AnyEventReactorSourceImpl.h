// Caramel C++ Library - Async Facility - Any Event Reactor Source Private Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_REACTOR_SOURCE_IMPL_H
#define __CARAMEL_ASYNC_ANY_EVENT_REACTOR_SOURCE_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Async/AnyEventTargetImpl.h"
#include <Caramel/Async/Detail/AnyEventReactorSource.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Reactor Source
//

class AnyEventReactorSource::Impl : public AnyEventTargetImpl
{
public:

    Impl( std::shared_ptr< AnyEventReactorImpl > reactor,
          std::function< void( const AnyEvent& ) > handler );

    /// Implements AnyEventTargetImpl ///

    void Send( const AnyEvent& event, Uint age ) override;


private:

    std::shared_ptr< AnyEventReactorImpl >   m_reactor;
    std::function< void( const AnyEvent& ) > m_handler;

    Uint m_reactorAge { 0 };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_REACTOR_SOURCE_IMPL_H
