// Caramel C++ Library - Async Facility - Any Event Front Private Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_FRONT_IMPL_H
#define __CARAMEL_ASYNC_ANY_EVENT_FRONT_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Async/AnyEventTargetImpl.h"


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Front
//

class AnyEventFrontImpl
{
public:

    explicit AnyEventFrontImpl( AnyEventTargetPtr hostTarget );

    void Pass( const AnyEvent& event );

private:

    AnyEventTargetPtr m_target;
    Uint m_age { 0 };
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_FRONT_IMPL_H
