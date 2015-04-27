// Caramel C++ Library - Async Facility - Any Event Target Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_TARGET_H
#define __CARAMEL_ASYNC_ANY_EVENT_TARGET_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEvent.h>
#include <functional>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Target
// - A target may be linked to an AnyEventDispatcher or AnyEventTask
//
//   The implementation should provide an AnyEventTargetPtr, which is
//   a std::shared_ptr. 
//

class AnyEventTargetImpl;
typedef std::shared_ptr< AnyEventTargetImpl > AnyEventTargetPtr;

struct AnyEventTarget
{
    virtual ~AnyEventTarget() {}
  
    // The implementation should have two effects:
    // 1. Unlink from all linked dispatchers.
    // 2. Discard all unprocessed events.
    virtual void Reset() = 0;

    // This function depends on GetTargetImpl().
    std::function< void( const AnyEvent& ) > AsHandler() const;


private:

    friend class AnyEventDispatcher;
    friend class AnyEventTask;

    // This is called by AnyEventDispatcher or AnyEventTask.
    virtual AnyEventTargetPtr GetTargetImpl() const = 0;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_TARGET_H
