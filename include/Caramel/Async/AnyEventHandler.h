// Caramel C++ Library - Async Amenity - Any Event Handler Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_HANDLER_H
#define __CARAMEL_ASYNC_ANY_EVENT_HANDLER_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/Detail/AnyEventHandlerImpl.h>
#include <Caramel/Async/AnyEventTarget.h>
#include <functional>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Handler
// - Send an event to this target would be passed to the executor.
//

class AnyEventHandler : public AnyEventTarget
{
public:
    
    typedef std::function< void( const AnyEvent& event ) > EventHandler;
    
    AnyEventHandler( TaskExecutor& executor, EventHandler handler );


private:

    /// Implements AnyEventTarget ///

    Detail::AnyEventTargetPtr GetTargetImpl() const override { return m_impl; }


    std::shared_ptr< Detail::AnyEventHandlerImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline AnyEventHandler::AnyEventHandler( TaskExecutor& executor, EventHandler handler )
    : m_impl( new Detail::AnyEventHandlerImpl( executor, std::move( handler )))
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_HANDLER_H
