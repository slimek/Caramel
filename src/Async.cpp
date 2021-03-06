// Caramel C++ Library - Async Facility - Implementation

#include "CaramelPch.h"

#include "Async/AnyEventDispatcherImpl.h"
#include "Async/AnyEventQueueImpl.h"
#include "Async/AnyEventReactorImpl.h"
#include "Async/AnyEventReactorSourceImpl.h"
#include "Async/AnyEventSlotImpl.h"
#include "Async/AnyEventTargetImpl.h"
#include "Async/AnyEventTargetProxyImpl.h"
#include <Caramel/Async/AnyEventHandler.h>
#include <Caramel/Async/AnyEventTask.h>


namespace Caramel
{

//
// Contents
//
//   AnyEventTarget
//   AnyEventQueue
//   AnyEventSlot
//   AnyEventDispatcher
//   AnyEventTargetProxyImpl
//   Detail::AnyEventQueueProxy
//   Detail::AnyEventDispatcherProxy
//   AnyEventReactor
//   Detail::AnyEventReactorSource
//   AnyEventHandler
//   AnyEventTask
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
// Temporary Queue Proxy
//

Detail::AnyEventQueueProxy AnyEventQueue::Proxy()
{
    return Detail::AnyEventQueueProxy( m_impl );
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


//
// Operations
//

void AnyEventSlot::Set( const AnyEvent& event )
{
    m_impl->SetEvent( event );
}


void AnyEventSlot::Set( AnyEvent&& event )
{
    m_impl->SetEvent( std::move( event ));
}


void AnyEventSlot::SetEvent( Int eventId )
{
    m_impl->SetEvent( AnyEvent( eventId ));
}


void AnyEventSlot::SetEvent( Int eventId, const Any& value )
{
    m_impl->SetEvent( AnyEvent( eventId, value ));
}


void AnyEventSlot::SetEvent( Int eventId, Any&& value )
{
    m_impl->SetEvent( AnyEvent( eventId, std::move( value )));
}


void AnyEventSlot::Wait()
{
    m_impl->Wait();
}


//
// Accessors
//

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

void AnyEventSlotImpl::SetEvent( const AnyEvent& event )
{
    LockGuard eventLock( m_eventMutex );
    if ( ! m_event.HasValue() )
    {
        m_event = event;
        m_becomesValid.notify_all();
        return;
    }

    // Not returned ? The slot already has an event, discard the new event.
    TraceDebug( "AnyEventSlot discard an event, id: {0}", event.Id() );
}


void AnyEventSlotImpl::SetEvent( AnyEvent&& event )
{
    LockGuard lock( m_eventMutex );
    if ( ! m_event.HasValue() )
    {
        m_event = std::move( event );
        m_becomesValid.notify_all();
        return;
    }

    // Not returned ? The slot already has an event, discard the new event.
    TraceDebug( "AnyEventSlot discard an event, id: {0}", event.Id() );
}


void AnyEventSlotImpl::Wait()
{
    UniqueLock ulock( m_eventMutex );

    while ( ! m_event.IsValid() )
    {
        m_becomesValid.wait( ulock );
    }
}


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
        this->SetEvent( event );
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


Usize AnyEventDispatcher::GetNumTargets() const
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
// Temporary Dispatcher Proxy
//

Detail::AnyEventDispatcherProxy AnyEventDispatcher::Proxy()
{
    return Detail::AnyEventDispatcherProxy( m_impl );
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
// Any Event Target Proxy
//

AnyEventTargetProxyImpl::AnyEventTargetProxyImpl( AnyEventTargetPtr hostTarget )
    : m_hostTarget( hostTarget )
    , m_hostAge( hostTarget->GetAge() )
{
}


void AnyEventTargetProxyImpl::SendToHost( const AnyEvent& event )
{
    m_hostTarget->Send( event, m_hostAge );
}


void AnyEventTargetProxyImpl::Send( const AnyEvent& event, Uint age )
{
    UniqueLock ulock = this->CompareAge( age );
    if ( ulock )
    {
        this->SendToHost( event );
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Any Event Queue Proxy
//

namespace Detail
{

AnyEventQueueProxy::AnyEventQueueProxy( AnyEventTargetPtr hostQueue )
    : m_impl( new AnyEventTargetProxyImpl( hostQueue ))
{
}


//
// Dispatch Events
//

void AnyEventQueueProxy::Push( const AnyEvent& event ) const
{
    m_impl->SendToHost( event );
}


void AnyEventQueueProxy::PushEvent( Int eventId ) const
{
    m_impl->SendToHost( AnyEvent( eventId ));
}


void AnyEventQueueProxy::PushEvent( Int eventId, const Any& value ) const
{
    m_impl->SendToHost( AnyEvent( eventId, value ));
}


void AnyEventQueueProxy::PushEvent( Int eventId, Any&& value ) const
{
    m_impl->SendToHost( AnyEvent( eventId, std::move( value )));
}

//
// Implements AnyEventTarget
//

void AnyEventQueueProxy::Reset()
{
    m_impl->IncrementAge();
}


AnyEventTargetPtr AnyEventQueueProxy::GetTargetImpl() const
{
    return m_impl;
}


} // namespace Detail


///////////////////////////////////////////////////////////////////////////////
//
// Any Event Dispatcher Proxy
//

namespace Detail
{

AnyEventDispatcherProxy::AnyEventDispatcherProxy( AnyEventTargetPtr hostDispatcher )
    : m_impl( new AnyEventTargetProxyImpl( hostDispatcher ))
{
}


//
// Dispatch Events
//

void AnyEventDispatcherProxy::Dispatch( const AnyEvent& event ) const
{
    m_impl->SendToHost( event );
}


void AnyEventDispatcherProxy::DispatchEvent( Int eventId ) const
{
    m_impl->SendToHost( AnyEvent( eventId ));
}


void AnyEventDispatcherProxy::DispatchEvent( Int eventId, const Any& value ) const
{
    m_impl->SendToHost( AnyEvent( eventId, value ));
}


void AnyEventDispatcherProxy::DispatchEvent( Int eventId, Any&& value ) const
{
    m_impl->SendToHost( AnyEvent( eventId, std::move( value )));
}


//
// Implements AnyEventTarget
//

void AnyEventDispatcherProxy::Reset()
{
    m_impl->IncrementAge();
}


AnyEventTargetPtr AnyEventDispatcherProxy::GetTargetImpl() const
{
    return m_impl;
}


} // namespace Detail


///////////////////////////////////////////////////////////////////////////////
//
// Any Event Reactor
//

AnyEventReactor::AnyEventReactor()
    : m_impl( new AnyEventReactorImpl )
{}


AnyEventReactor::~AnyEventReactor()
{}


Detail::AnyEventReactorSource
AnyEventReactor::Receive( std::function< void( const AnyEvent& ) > handler )
{
    CARAMEL_ASSERT( handler );

    return Detail::AnyEventReactorSource(
        std::make_shared< Detail::AnyEventReactorSource::Impl >( m_impl, handler ));
}


void AnyEventReactor::PollOne()
{
    m_impl->PollOne();
}


void AnyEventReactor::Reset()
{
    m_impl->IncrementAge();
    m_impl->Clear();
}


//
// Implementation
//

void AnyEventReactorImpl::Emit( Entry&& entry, Uint age )
{
    auto ulock = this->CompareAge( age );
    if ( ulock )
    {
        m_entries.Push( std::move( entry ));
    }
}


void AnyEventReactorImpl::PollOne()
{
    Entry e;
    if ( m_entries.TryPop( e ))
    {
        if ( ! e.handler )
        {
            if ( e.event.IsValid() )
            {
                CARAMEL_ALERT( "Handler is invalid, event id: {0}", e.event.Id() );
            }
            else
            {
                CARAMEL_ALERT( "Handler is invalid" );
            }
            return;
        }

        e.handler( e.event );
    }
}


void AnyEventReactorImpl::Clear()
{
    m_entries.Clear();
}


//
// Reference Aging
//

void AnyEventReactorImpl::IncrementAge()
{
    UniqueLock ulock( m_ageMutex );
    ++ m_age;
}


UniqueLock AnyEventReactorImpl::CompareAge( Uint age ) const
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
// Any Event Reactor Source
//

namespace Detail
{

AnyEventReactorSource::AnyEventReactorSource( std::shared_ptr< Impl > impl )
    : m_impl( impl )
    , m_null( std::make_shared< std::nullptr_t >() )
{}


AnyEventReactorSource::~AnyEventReactorSource()
{
    if ( m_null.unique() )  // This is the last copy of a source.
    {
        m_impl->Destroy();
    }
}


void AnyEventReactorSource::Reset()
{
    m_impl->IncrementAge();
}


AnyEventTargetPtr AnyEventReactorSource::GetTargetImpl() const
{
    return m_impl;
}


//
// Implementation
//

AnyEventReactorSource::Impl::Impl(
    std::shared_ptr< AnyEventReactorImpl > reactor,
    std::function< void( const AnyEvent& ) > handler )
    : m_reactor( reactor )
    , m_handler( handler )
    , m_reactorAge( reactor->GetAge() )
{
}


void AnyEventReactorSource::Impl::Send( const AnyEvent& event, Uint age )
{
    auto ulock = this->CompareAge( age );
    if ( ulock )
    {
        m_reactor->Emit( { event, m_handler }, m_reactorAge );
    }
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
//
// Any Event Task
//

AnyEventTask::AnyEventTask()
    : Task< AnyEvent >()
{
}


AnyEventTask::AnyEventTask( Task< AnyEvent > task )
    : Task< AnyEvent >( std::move( task ))
{
}


void AnyEventTask::Link( AnyEventTarget& target )
{
    auto targetImpl = target.GetTargetImpl();
    const auto age = targetImpl->GetAge();

    this->Then(
    [=] ( const Task< AnyEvent >& task )
    {
        targetImpl->Send( task.GetResult(), age );
    });
}


Int AnyEventTask::Id() const
{
    return this->GetResult().Id();
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Caramel
