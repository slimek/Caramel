// Caramel C++ Library - Async Amenity - Detail - Any Event Handler Private Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_HANDLER_IMPL_H
#define __CARAMEL_ASYNC_ANY_EVENT_HANDLER_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/Detail/AnyEventTargetImpl.h>
#include <Caramel/String/Format.h>
#include <Caramel/Task/TaskExecutor.h>


namespace Caramel
{

namespace Detail
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
//
// Implementation
//

inline AnyEventHandlerImpl::AnyEventHandlerImpl( TaskExecutor& executor, EventHandler&& handler )
    : m_executor( executor )
    , m_handler( std::move( handler ))
{
}


inline void AnyEventHandlerImpl::Send( const AnyEvent& event, Uint age )
{
    UniqueLock ulock = this->CompareAge( age );
    if ( ulock )
    {
        auto thiz = this->shared_from_this();

        Task< void > task( Format( "Event %d", event.Id() ),
        [thiz,event]
        {
            thiz->m_handler( event );
        });

        m_executor.Submit( task );
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_HANDLER_IMPL_H
