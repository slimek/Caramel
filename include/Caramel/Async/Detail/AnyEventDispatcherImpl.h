// Caramel C++ Library - Async Amenity - Detail - Any Event Dispatcher Private Header

#ifndef __CARAMEL_ASYNC_DETAIL_ANY_EVENT_DISPATCHER_IMPL_H
#define __CARAMEL_ASYNC_DETAIL_ANY_EVENT_DISPATCHER_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEvent.h>
#include <Caramel/Async/Detail/AnyEventTargetImpl.h>
#include <Caramel/Concurrent/HashMap.h>


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

    void Send( const AnyEvent& evt, Uint age ) override;


private:

    Int m_minEventId;
    Int m_maxEventId;

    typedef Concurrent::HashMapWithSnapshot< AnyEventTargetPtr, Uint > TargetMap;
    TargetMap m_targets;
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
    m_targets.Insert( std::move( target ), target->GetAge() );
}


inline void AnyEventDispatcherImpl::UnlinkTarget( const AnyEventTargetPtr& target )
{
    m_targets.Erase( target );
}


//
// Operations
//

inline void AnyEventDispatcherImpl::Dispatch( const AnyEvent& event )
{
    auto targets = m_targets.GetPairsSnapshot();

    for ( auto pair : targets )
    {
        auto target = pair.first;
        const Uint age = pair.second;

        if ( target->IsDestroyed() || target->GetAge() > age )
        {
            m_targets.Erase( target );
            continue;
        }

        target->Send( event, age );
    }
}


inline void AnyEventDispatcherImpl::Send( const AnyEvent& event, Uint age )
{
    UniqueLock ulock = this->CompareAge( age );
    if ( ulock )
    {
        this->Dispatch( event );
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Detail

} // namespace Caramel

#endif // __CARAMEL_ASYNC_DETAIL_ANY_EVENT_DISPATCHER_IMPL_H
