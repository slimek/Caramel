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
// - Send an event to this target would result in an immediately function call.
//

class AnyEventHandler : public AnyEventTarget
{
public:
    
    typedef std::function< void( const AnyEvent& event ) > EventHandler;
    
    explicit AnyEventHandler( EventHandler handler );


private:

    /// Implements AnyEventTarget ///

    Detail::AnyEventTargetPtr GetTargetImpl() const override;

    std::shared_ptr< Detail::AnyEventHandlerImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline AnyEventHandler::AnyEventHandler( EventHandler handler )
    : m_impl( new Detail::AnyEventHandlerImpl( std::move( handler )))
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_HANDLER_H
