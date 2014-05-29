// Caramel C++ Library - Async Facility - Any Event Handler Private Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_HANDLER_IMPL_H
#define __CARAMEL_ASYNC_ANY_EVENT_HANDLER_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Async/AnyEventTargetImpl.h"
#include <Caramel/Async/AnyEventHandler.h>
#include <Caramel/String/Format.h>
#include <Caramel/Task/TaskExecutor.h>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Handler
//

class AnyEventHandlerImpl : public AnyEventTargetImpl
                          , public std::enable_shared_from_this< AnyEventHandlerImpl >
{
public:

    typedef std::function< void( const AnyEvent& event ) > EventHandler;

    AnyEventHandlerImpl( TaskExecutor& executor, EventHandler&& handler );


    /// Implements AnyEventTargetImpl ///

    void Send( const AnyEvent& event, Uint age ) override;


private:

    /// Data Members ///

    TaskExecutor& m_executor;
    EventHandler  m_handler;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_HANDLER_IMPL_H
