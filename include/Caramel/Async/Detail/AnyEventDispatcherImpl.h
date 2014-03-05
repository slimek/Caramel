// Caramel C++ Library - Async Amenity - Detail - Any Event Dispatcher Private Header

#ifndef __CARAMEL_ASYNC_DETAIL_ANY_EVENT_DISPATCHER_IMPL_H
#define __CARAMEL_ASYNC_DETAIL_ANY_EVENT_DISPATCHER_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Async/AnyEvent.h>
#include <Caramel/Async/Detail/AnyEventTargetImpl.h>
#include <Caramel/Concurrent/Set.h>


namespace Caramel
{

namespace Detail
{

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Dispatcher
//

class AnyEventDispatcherImpl : public AnyEventTargetImpl
{
public:

    AnyEventDispatcherImpl( Int minEventId, Int maxEventId );

    
    /// Targets Management ///

    void LinkTarget( AnyEventTargetPtr&& target );
    void UnlinkTarget( const AnyEventTargetPtr& target );

    Uint GetNumTargets() const { return m_targets.Size(); }


    /// Operations ///

    void Dispatch( const AnyEvent& evt );


    /// Implements AnyEventTargetImpl ///

    void Send( const AnyEvent& evt ) override { this->Dispatch( evt ); }


private:

    Int m_minEventId;
    Int m_maxEventId;

    typedef Concurrent::SetWithSnapshot< AnyEventTargetPtr > TargetSet;
    TargetSet m_targets;
};


///////////////////////////////////////////////////////////////////////////////
//
// Implementation
//

inline AnyEventDispatcherImpl::AnyEventDispatcherImpl( Int minEventId, Int maxEventId )
    : m_minEventId( minEventId )
    , m_maxEventId( maxEventId )
{
}


//
// Targets Management
//

inline void AnyEventDispatcherImpl::LinkTarget( AnyEventTargetPtr&& target )
{
    m_targets.Insert( std::move( target ));
}


inline void AnyEventDispatcherImpl::UnlinkTarget( const AnyEventTargetPtr& target )
{
    m_targets.Erase( target );
}


//
// Operations
//

inline void AnyEventDispatcherImpl::Dispatch( const AnyEvent& evt )
{
    auto targets = m_targets.GetSnapshot();

    for ( auto target : targets )
    {
        if ( target->IsDestroyed() )
        {
            m_targets.Erase( target );
            continue;
        }

        target->Send( evt );
    }
}




///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ASYNC_DETAIL_ANY_EVENT_DISPATCHER_IMPL_H
