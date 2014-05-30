// Caramel C++ Library - Async Facility - Implementation

#include "CaramelPch.h"

#include "Async/AnyEventDispatcherImpl.h"
#include "Async/AnyEventQueueImpl.h"
#include "Async/AnyEventSlotImpl.h"
#include "Async/AnyEventTargetImpl.h"


namespace Caramel
{

//
// Contents
//
//   AnyEventTarget
//   AnyEventQueue
//   AnyEventSlot
//   AnyEventDispatcher
//

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Target
//

AnyEventTargetImpl::AnyEventTargetImpl()
    : m_destroyed( false )
    , m_age( 0 )
{
}


void AnyEventTargetImpl::Destroy()
{
    CARAMEL_ASSERT( ! m_destroyed );
    m_destroyed = true;
}


//
// Reference Aging
//

void AnyEventTargetImpl::IncrementAge()
{
    UniqueLock ulock( m_ageMutex );
    ++ m_age;
}


UniqueLock AnyEventTargetImpl::CompareAge( Uint age ) const
{
    UniqueLock ulock( m_ageMutex );
    if ( m_age != age )
    {
        ulock.unlock();
    }
    return std::move( ulock );
}


///////////////////////////////////////////////////////////////////////////////
//
// Any Event Queue
//

AnyEventQueue::AnyEventQueue()
    : m_impl( new AnyEventQueueImpl )
{
}


AnyEventQueue::~AnyEventQueue()
{
    m_impl->Destroy();
}


AnyEventTargetPtr AnyEventQueue::GetTargetImpl() const
{
    return m_impl;
}


//
// Operations
//

void AnyEventQueue::Push( const AnyEvent& evt )
{
    m_impl->Push( evt );
}


void AnyEventQueue::Push( AnyEvent&& evt )
{
    m_impl->Push( std::move( evt ));
}


void AnyEventQueue::PushEvent( Int eventId )
{
    m_impl->Push( AnyEvent( eventId ));
}


void AnyEventQueue::PushEvent( Int eventId, const Any& any )
{
    m_impl->Push( AnyEvent( eventId, any ));
}


void AnyEventQueue::PushEvent( Int eventId, Any&& any )
{
    m_impl->Push( AnyEvent( eventId, std::move( any )));
}


Bool AnyEventQueue::TryPop( AnyEvent& evt )
{
    return m_impl->TryPop( evt );
}


void AnyEventQueue::UnlinkAll()
{
    m_impl->IncrementAge();
    m_impl->Clear();
}


//
// To Prevent Ambiguous IDs
//

Bool AnyEventQueue::RegisterIdRange( Int minEventId, Int maxEventId )
{
    return m_impl->RegisterIdRange( minEventId, maxEventId );
}


void AnyEventQueue::UnregisterIdRange( Int minEventId, Int maxEventId )
{
    m_impl->UnregisterIdRange( minEventId, maxEventId );
}


//
// Implementation
//

void AnyEventQueueImpl::Send( const AnyEvent& evt, Uint age )
{
    UniqueLock ulock = this->CompareAge( age );
    if ( ulock )
    {
        this->Push( evt );
    }
}


//
// To Prevent Ambiguous IDs
//

Bool AnyEventQueueImpl::RegisterIdRange( Int minEventId, Int maxEventId )
{
    return m_registeredIdRanges.InsertClosed( minEventId, maxEventId );
}


void AnyEventQueueImpl::UnregisterIdRange( Int minEventId, Int maxEventId )
{
    m_registeredIdRanges.EraseClosed( minEventId, maxEventId );
}


///////////////////////////////////////////////////////////////////////////////
//
// Any Event Slot
//

AnyEventSlot::AnyEventSlot()
    : m_impl( new AnyEventSlotImpl )
{
}


AnyEventSlot::~AnyEventSlot()
{
    m_impl->Destroy();
}


AnyEventTargetPtr AnyEventSlot::GetTargetImpl() const
{
    return m_impl;
}


Bool AnyEventSlot::IsValid() const
{
    return m_impl->GetEvent().IsValid();
}


AnyEvent AnyEventSlot::GetEvent() const
{
    const AnyEvent event = m_impl->GetEvent();
    if ( ! event.IsValid() )
    {
        CARAMEL_THROW( "AnyEventSlot is empty" );
    }
    return event;
}


void AnyEventSlot::UnlinkAll()
{
    m_impl->IncrementAge();
    m_impl->Clear();
}


//
// Implementation
//

AnyEvent AnyEventSlotImpl::GetEvent() const
{
    LockGuard lock( m_eventMutex );
    return m_event;
}


void AnyEventSlotImpl::Send( const AnyEvent& event, Uint age )
{
    UniqueLock ulock = this->CompareAge( age );
    if ( ulock )
    {
        {
            LockGuard eventLock( m_eventMutex );
            if ( ! m_event.HasValue() )
            {
                m_event = event;
                return;
            }
        }

        // Not returns ? The event has already existed, discard the new event.
        CARAMEL_TRACE_DEBUG( "AnyEventSlot discard an event, id: %d", event.Id() );
    }
}


void AnyEventSlotImpl::Clear()
{
    LockGuard lock( m_eventMutex );
    m_event = AnyEvent();
}


///////////////////////////////////////////////////////////////////////////////
//
// Any Event Dispatcher
//

AnyEventDispatcher::AnyEventDispatcher( Int minEventId, Int maxEventId )
    : m_impl( new AnyEventDispatcherImpl( minEventId, maxEventId ))
{
}


AnyEventDispatcher::~AnyEventDispatcher()
{
    m_impl->Destroy();
}


AnyEventTargetPtr AnyEventDispatcher::GetTargetImpl() const
{
    return m_impl;
}


//
// Targets Management
//

void AnyEventDispatcher::LinkTarget( AnyEventTarget& target )
{
    m_impl->LinkTarget( target.GetTargetImpl() );
}


void AnyEventDispatcher::UnlinkTarget( AnyEventTarget& target )
{
    m_impl->UnlinkTarget( target.GetTargetImpl() );
}


Uint AnyEventDispatcher::GetNumTargets() const
{
    return m_impl->GetNumTargets();
}


//
// Operations
//

void AnyEventDispatcher::DispatchEvent( Int eventId )
{
    m_impl->Dispatch( AnyEvent( eventId ));
}


void AnyEventDispatcher::DispatchEvent( Int eventId, const Any& value )
{
    m_impl->Dispatch( AnyEvent( eventId, value ));
}


void AnyEventDispatcher::DispatchEvent( Int eventId, Any&& value )
{
    m_impl->Dispatch( AnyEvent( eventId, std::move( value )));
}


void AnyEventDispatcher::Dispatch( const AnyEvent& evt )
{
    m_impl->Dispatch( evt );
}


//
// Implementation
//

AnyEventDispatcherImpl::AnyEventDispatcherImpl( Int minEventId, Int maxEventId )
    : m_minEventId( minEventId )
    , m_maxEventId( maxEventId )
{
}


//
// Targets Management
//

void AnyEventDispatcherImpl::LinkTarget( AnyEventTargetPtr&& target )
{
    m_targets.Insert( std::move( target ), target->GetAge() );
}


void AnyEventDispatcherImpl::UnlinkTarget( const AnyEventTargetPtr& target )
{
    m_targets.Erase( target );
}


//
// Operations
//

void AnyEventDispatcherImpl::Dispatch( const AnyEvent& event )
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


void AnyEventDispatcherImpl::Send( const AnyEvent& event, Uint age )
{
    UniqueLock ulock = this->CompareAge( age );
    if ( ulock )
    {
        this->Dispatch( event );
    }
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
