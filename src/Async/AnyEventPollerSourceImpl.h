// Caramel C++ Library - Async Facility - Any Event Poller Source Private Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_POLLER_SOURCE_IMPL_H
#define __CARAMEL_ASYNC_ANY_EVENT_POLLER_SOURCE_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Async/AnyEventTargetImpl.h"
#include <Caramel/Async/Detail/AnyEventPollerSource.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Poller Source
//

class AnyEventPollerSource::Impl : public AnyEventTargetImpl
{
public:

    Impl( std::shared_ptr< AnyEventPollerImpl > poller,
          std::function< void( const AnyEvent& ) > handler );

    /// Implements AnyEventTargetImpl ///

    void Send( const AnyEvent& event, Uint age ) override;


private:

    std::shared_ptr< AnyEventPollerImpl >    m_poller;
    std::function< void( const AnyEvent& ) > m_handler;

    Uint m_pollerAge { 0 };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_POLLER_SOURCE_IMPL_H
