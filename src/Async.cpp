// Caramel C++ Library - Async Facility - Implementation

#include "CaramelPch.h"

#include "Async/AnyEventDispatcherImpl.h"
#include "Async/AnyEventFrontImpl.h"
#include "Async/AnyEventQueueImpl.h"
#include "Async/AnyEventSlotImpl.h"
#include "Async/AnyEventTargetImpl.h"
#include <Caramel/Async/AnyEventHandler.h>


namespace Caramel
{

//
// Contents
//
//   AnyEventTarget
//   AnyEventQueue
//   AnyEventSlot
//   AnyEventDispatcher
//   Detail::AnyEventQueueFront
//   Detail::AnyEventDispatcherFront
//   AnyEventHandler
//

///////////////////////////////////////////////////////////////////////////////
//
// Any Event Target
//

std::function< void( const AnyEvent& ) > AnyEventTarget::AsHandler() const
{
    auto target = this->GetTargetImpl();
    const Uint age = target->GetAge();

    return std::bind(
        &AnyEventTargetImpl::Send,
        target, std::placeholders::_1, age
    );
}


//
// Implementation
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

void AnyEventQueue::Push( const AnyEvent& event )
{
    m_impl->Push( event );
}

void AnyEventQueue::Push( AnyEvent&& event )
{
    m_impl->Push( std::move( event ));
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


Bool AnyEventQueue::TryPop( AnyEvent& event )
{
    return m_impl->TryPop( event );
}


void AnyEventQueue::Reset()
{
    m_impl->IncrementAge();
    m_impl->Clear();
}


//
// Temporary Front Dispatcher
//

Detail::AnyEventQueueFront AnyEventQueue::Front()
{
    return Detail::AnyEventQueueFront( m_impl );
}


//
// Implementation
//

void AnyEventQueueImpl::Send( const AnyEvent& event, Uint age )
{
    UniqueLock ulock = this->CompareAge( age );
    if ( ulock )
    {
        this->Push( event );
    }
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


AnyEvent AnyEventSlot::Take()
{
    AnyEvent event;
    if ( ! m_impl->TryTake( event ))
    {
        CARAMEL_THROW( "AnyEventSlot is empty" );
    }
    return std::move( event );
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


void AnyEventSlot::Reset()
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


Bool AnyEventSlotImpl::TryTake( AnyEvent& event )
{
    LockGuard lock( m_eventMutex );
    if ( ! m_event.IsValid() ) { return false; }

    event = AnyEvent();
    std::swap( event, m_event );
    return true;
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

AnyEventDispatcher::AnyEventDispatcher()
    : m_impl( new AnyEventDispatcherImpl )
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

void AnyEventDispatcher::Dispatch( const AnyEvent& event )
{
    m_impl->Dispatch( event );
}


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


//
// Temporary Front Dispatcher
//

Detail::AnyEventDispatcherFront AnyEventDispatcher::Front()
{
    return Detail::AnyEventDispatcherFront( m_impl );
}


//
// AnyEventTarget Operations
//

void AnyEventDispatcher::Reset()
{
    m_impl->IncrementAge();
}


//
// Implementation
//

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
//
// Any Event Front
//

AnyEventFrontImpl::AnyEventFrontImpl( AnyEventTargetPtr target )
    : m_target( target )
    , m_age( target->GetAge() )
{
}


void AnyEventFrontImpl::Pass( const AnyEvent& event )
{
    m_target->Send( event, m_age );
}


///////////////////////////////////////////////////////////////////////////////
//
// Any Event Queue Front
//

namespace Detail
{

AnyEventQueueFront::AnyEventQueueFront( AnyEventTargetPtr hostQueue )
    : m_impl( new AnyEventFrontImpl( hostQueue ))
{
}


//
// Dispatch Events
//

void AnyEventQueueFront::Push( const AnyEvent& event ) const
{
    m_impl->Pass( event );
}


void AnyEventQueueFront::PushEvent( Int eventId ) const
{
    m_impl->Pass( AnyEvent( eventId ));
}


void AnyEventQueueFront::PushEvent( Int eventId, const Any& value ) const
{
    m_impl->Pass( AnyEvent( eventId, value ));
}


void AnyEventQueueFront::PushEvent( Int eventId, Any&& value ) const
{
    m_impl->Pass( AnyEvent( eventId, std::move( value )));
}

} // namespace Detail


///////////////////////////////////////////////////////////////////////////////
//
// Any Event Dispatcher Front
//

namespace Detail
{

AnyEventDispatcherFront::AnyEventDispatcherFront( AnyEventTargetPtr hostDispatcher )
    : m_impl( new AnyEventFrontImpl( hostDispatcher ))
{
}


//
// Dispatch Events
//

void AnyEventDispatcherFront::Dispatch( const AnyEvent& event ) const
{
    m_impl->Pass( event );
}


void AnyEventDispatcherFront::DispatchEvent( Int eventId ) const
{
    m_impl->Pass( AnyEvent( eventId ));
}


void AnyEventDispatcherFront::DispatchEvent( Int eventId, const Any& value ) const
{
    m_impl->Pass( AnyEvent( eventId, value ));
}


void AnyEventDispatcherFront::DispatchEvent( Int eventId, Any&& value ) const
{
    m_impl->Pass( AnyEvent( eventId, std::move( value )));
}


} // namespace Detail


///////////////////////////////////////////////////////////////////////////////
//
// Any Event Handler
//

AnyEventHandler::AnyEventHandler()
    : m_handler( nullptr )
{
}


AnyEventHandler::AnyEventHandler( std::nullptr_t )
    : m_handler( nullptr )
{
}


AnyEventHandler::AnyEventHandler( const AnyEventHandler& other )
    : m_handler( other.m_handler )
{
}


AnyEventHandler::AnyEventHandler( AnyEventHandler&& other )
    : m_handler( std::move( other.m_handler ))
{
}


AnyEventHandler AnyEventHandler::Empty()
{
    return AnyEventHandler( [] ( const AnyEvent& ) {} );  // Returns an empty handler.
}


void AnyEventHandler::InitFromTarget( AnyEventTarget& target )
{
    m_handler = target.AsHandler();
}


void AnyEventHandler::operator()( const AnyEvent& event ) const
{
    m_handler( event );
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
