// Caramel C++ Library - Async Facility - Any Event Handler Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_HANDLER_H
#define __CARAMEL_ASYNC_ANY_EVENT_HANDLER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEventTarget.h>
#include <Caramel/Task/Detail/TaskFwd.h>
#include <functional>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Handler
// - Send an event to this target would be passed to the executor.
//

class AnyEventHandlerImpl;

class AnyEventHandler : public AnyEventTarget
{
public:
    
    typedef std::function< void( const AnyEvent& event ) > EventHandler;
    
    AnyEventHandler( TaskExecutor& executor, EventHandler handler );


private:

    /// Implements AnyEventTarget ///

    AnyEventTargetPtr GetTargetImpl() const override;


    /// Data Members ///

    std::shared_ptr< AnyEventHandlerImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_HANDLER_H
