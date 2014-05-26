// Caramel C++ Library - Async Amenity - Detail - Any Event Handler Private Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_HANDLER_IMPL_H
#define __CARAMEL_ASYNC_ANY_EVENT_HANDLER_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/Detail/AnyEventTargetImpl.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Handler
//

class AnyEventHandlerImpl : public AnyEventTargetImpl
{
public:

    typedef std::function< void( const AnyEvent& event ) > EventHandler;

    explicit AnyEventHandlerImpl( EventHandler&& handler );


    /// Implements AnyEventTargetImpl ///

    void Send( const AnyEvent& event, Uint age ) override;


private:

    /// Data Members ///

    EventHandler m_handler;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline AnyEventHandlerImpl::AnyEventHandlerImpl( EventHandler&& handler )
    : m_handler( std::move( handler ))
{
}


inline void AnyEventHandlerImpl::Send( const AnyEvent& event, Uint age )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_HANDLER_IMPL_H
