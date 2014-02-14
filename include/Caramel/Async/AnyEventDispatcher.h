// Caramel C++ Library - Async Amenity - Any Event Dispatcher Header

#ifndef __CARAMEL_ASYNC_ANY_EVENT_DISPATCHER_H
#define __CARAMEL_ASYNC_ANY_EVENT_DISPATCHER_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Async/AnyEventTarget.h>
#include <Caramel/Async/Detail/AnyEventDispatcherImpl.h>
#include <boost/noncopyable.hpp>


namespace Caramel
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Dispatcher
//

class AnyEventDispatcher : public AnyEventTarget
                         , public boost::noncopyable
{
public:

    AnyEventDispatcher( Int minEventId, Int maxEventId );
    ~AnyEventDispatcher();


    /// Targets Management ///

    void LinkTarget( AnyEventTarget& target );
    void UnlinkTarget( AnyEventTarget& target );


    /// Dispatch Events to Targets ///

    void Dispatch( const AnyEvent& evt );

    void DispatchEvent( Int eventId );
    void DispatchEvent( Int eventId, const Any& value );
    void DispatchEvent( Int eventId, Any&& value );


    /// Implements AnyEventTarget ///

    Detail::AnyEventTargetPtr GetImpl() const override { return m_impl; }


private:

    /// Data Members ///

    std::shared_ptr< Detail::AnyEventDispatcherImpl > m_impl;          
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline AnyEventDispatcher::AnyEventDispatcher( Int minEventId, Int maxEventId )
    : m_impl( new Detail::AnyEventDispatcherImpl( minEventId, maxEventId ))
{
}


inline AnyEventDispatcher::~AnyEventDispatcher()
{
    m_impl->Destroy();
}


//
// Targets Management
//

inline void AnyEventDispatcher::LinkTarget( AnyEventTarget& target )
{
    m_impl->LinkTarget( target.GetImpl() );
}


inline void AnyEventDispatcher::UnlinkTarget( AnyEventTarget& target )
{
    m_impl->UnlinkTarget( target.GetImpl() );
}


//
// Operations
//

inline void AnyEventDispatcher::DispatchEvent( Int eventId )
{
    m_impl->Dispatch( AnyEvent( eventId ));
}


inline void AnyEventDispatcher::DispatchEvent( Int eventId, const Any& value )
{
    m_impl->Dispatch( AnyEvent( eventId, value ));
}


inline void AnyEventDispatcher::DispatchEvent( Int eventId, Any&& value )
{
    m_impl->Dispatch( AnyEvent( eventId, std::move( value )));
}


inline void AnyEventDispatcher::Dispatch( const AnyEvent& evt )
{
    m_impl->Dispatch( evt );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel

#endif // __CARAMEL_ASYNC_ANY_EVENT_DISPATCHER_H
