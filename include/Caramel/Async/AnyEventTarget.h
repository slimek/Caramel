// Caramel C++ Library - Async Facility - Any Event Target Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_TARGET_H
#define __CARAMEL_ASYNC_ANY_EVENT_TARGET_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEvent.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Target
//

class AnyEventTargetImpl;
typedef std::shared_ptr< AnyEventTargetImpl > AnyEventTargetPtr;

struct AnyEventTarget
{
    virtual ~AnyEventTarget() {}
  
    virtual AnyEventTargetPtr GetTargetImpl() const = 0;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_TARGET_H
