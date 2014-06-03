// Caramel C++ Library - Async Facility - Any Event Queue Private Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_QUEUE_IMPL_H
#define __CARAMEL_ASYNC_ANY_EVENT_QUEUE_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Async/AnyEventTargetImpl.h"
#include <Caramel/Async/AnyEventQueue.h>
#include <Caramel/Concurrent/Queue.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Queue
//

class AnyEventQueueImpl : public Concurrent::Queue< AnyEvent >
                        , public AnyEventTargetImpl
{
public:

    /// Implements AnyEventTargetImpl ///

    void Send( const AnyEvent& evt, Uint age ) override;

};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_QUEUE_IMPL_H
