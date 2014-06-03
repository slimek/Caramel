// Caramel C++ Library - Async Facility - Any Event Slot Private Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_SLOT_IMPL_H
#define __CARAMEL_ASYNC_ANY_EVENT_SLOT_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Async/AnyEventTargetImpl.h"
#include <Caramel/Async/AnyEventSlot.h>
#include <mutex>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Slot
//

class AnyEventSlotImpl : public AnyEventTargetImpl
{
public:

    AnyEvent GetEvent() const;
    Bool TryTake( AnyEvent& event );

    void Clear();

    /// Implements AnyEventTargetImpl ///

    void Send( const AnyEvent& event, Uint age ) override;

private:

    AnyEvent m_event;
    mutable std::mutex m_eventMutex;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_SLOT_IMPL_H
