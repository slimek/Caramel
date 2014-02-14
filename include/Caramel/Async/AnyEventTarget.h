// Caramel C++ Library - Async Amenity - Any Event Target Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_TARGET_H
#define __CARAMEL_ASYNC_ANY_EVENT_TARGET_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Async/Detail/AnyEventTargetImpl.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Target
//

struct AnyEventTarget
{
    virtual ~AnyEventTarget() {}
  
    virtual Detail::AnyEventTargetPtr GetImpl() const = 0;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_TARGET_H
