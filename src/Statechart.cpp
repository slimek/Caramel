// Caramel C++ Library - Statechart Facility - Implementation

#include "CaramelPch.h"

#include "Statechart/StateImpl.h"
#include "Statechart/StateMachineImpl.h"
#include "Statechart/Transition.h"
#include <Caramel/Error/CatchException.h>
#include <Caramel/Functional/ScopeExit.h>
#include <Caramel/Task/TaskPoller.h>
#include <Caramel/Thread/ThisThread.h>


namespace Caramel
{

namespace Statechart
{

//
// Contents
//
//   StateMachine
//   State
//

///////////////////////////////////////////////////////////////////////////////
//
// State Machine
//

StateMachine::StateMachine( const std::string& name )
    : m_impl( new StateMachineImpl( name ))
{
}


StateMachine::~StateMachine()
{
    // Notify all linked dispatchers to unlink this.
    m_impl->Destroy();
}


//
// Operations
//

State StateMachine::AddState( Int stateId )
{
    CARAMEL_CHECK( ! m_impl->m_initiated );

    StatePtr newState = std::make_shared< StateImpl >( stateId, m_impl->m_name );
    if ( ! m_impl->m_states.Insert( stateId, newState ))
    {
        CARAMEL_THROW( "State duplicate, machine: %s, stateId: %d", m_impl->m_name, stateId );
    }
    return State( newState );
}


void StateMachine::Initiate( Int stateId )
{
    CARAMEL_CHECK( ! m_impl->m_initiated );

    StatePtr initialState;
    if ( ! m_impl->m_states.Find( stateId, initialState ))
    {
        CARAMEL_THROW( "State not found, machine: %s, stateId: %d", m_impl->m_name, stateId );
    }

    m_impl->m_currentState = initialState;
    m_impl->m_initiated = true;
}


void StateMachine::PostEvent( Int eventId )
{
    this->PostEvent( AnyEvent( eventId ));
}


void StateMachine::PostEvent( Int eventId, const Any& value )
{
    this->PostEvent( AnyEvent( eventId, value ));
}


void StateMachine::PostEvent( const AnyEvent& evt )
{
    m_impl->PostEvent( evt );
}


void StateMachine::Process( const Ticks& sliceTicks )
{
    CARAMEL_CHECK( m_impl->m_builtinTaskPoller );
    CARAMEL_CHECK( m_impl->m_initiated );

    m_impl->m_builtinTaskPoller->PollFor( sliceTicks );
}


//
// Properties
//

Int StateMachine::GetCurrentStateId() const
{
    return m_impl->m_currentState->GetId();
}


AnyEvent StateMachine::GetActiveEvent() const
{
    return m_impl->m_activeEvent;
}


//
// Implementation
//

StateMachineImpl::StateMachineImpl( const std::string& name )
    : m_name( name )
    , m_taskExecutor( nullptr )
    , m_builtinTaskPoller( new TaskPoller )
    , m_initiated( false )
    , m_transitNumber( 0 )
{
    m_taskExecutor = m_builtinTaskPoller.get();
}


void StateMachineImpl::PostEvent( const AnyEvent& evt )
{
    CARAMEL_CHECK( m_initiated );

    auto task = MakeTask(
        Sprintf( "Machine[%s].ProcessEvent[%d]", m_name, evt.Id() ),
        [=] { this->ProcessEvent( evt ); }
    );

    this->m_taskExecutor->Submit( task );
}


void StateMachineImpl::ProcessEvent( const AnyEvent& evt )
{
    LockGuard lock( m_mutex );

    m_actionThreadId = ThisThread::GetId();
    auto tidGuard = ScopeExit( [=] { m_actionThreadId = ThreadId(); } );

    m_activeEvent = evt;
    auto evtGuard = ScopeExit( [=] { m_activeEvent = AnyEvent(); } );

    TransitionPtr transition;
    if ( m_currentState->m_transitions.Find( evt.Id(), transition ))
    {
        StatePtr targetState;
        CARAMEL_VERIFY( m_states.Find( transition->targetStateId, targetState ));

        this->DoTransit( transition, targetState );
        return;
    }

    // Otherwise, discard this event
    CARAMEL_TRACE_DEBUG( "%s discards event %d", m_currentState->GetName(), evt.Id() );
}


void StateMachineImpl::DoTransit( TransitionPtr transition, StatePtr targetState )
{
    // REMARKS: At this point, the m_mutex should have been locked.

    this->ExitState();

    if ( transition->action )
    {
        transition->action();
    }

    m_currentState = targetState;

    this->EnterState();
}


void StateMachineImpl::StartTimer( const Ticks& ticks )
{
    CARAMEL_NOT_IMPLEMENTED();
}


//
// State Actions
//

void StateMachineImpl::EnterState()
{
    ++ m_transitNumber;
    m_currentStartTime = TickClock::Now();

    if ( m_currentState->m_enterAction )
    {
        auto xc = CatchException( [=] { m_currentState->m_enterAction(); } );
        if ( xc )
        {
            CARAMEL_TRACE_WARN( "%s enter action throws:\n%s",
                                m_currentState->GetName(), xc.TracingMessage() );
        }
    }

    if ( Ticks::Zero() < m_currentState->m_autoTimerDuration )
    {
        this->StartTimer( m_currentState->m_autoTimerDuration );
    }
}


void StateMachineImpl::ExitState()
{
    // TODO: Cancel the timer.

    if ( m_currentState->m_exitAction )
    {
        auto xc = CatchException( [=] { m_currentState->m_exitAction(); } );
        if ( xc )
        {
            CARAMEL_TRACE_WARN( "%s exit action throws:\n%s",
                                m_currentState->GetName(), xc.TracingMessage() );
        }
    }
}


//
// Implements AnyEventTarget
//

Detail::AnyEventTargetPtr StateMachine::GetImpl() const
{
    return m_impl;
}


void StateMachineImpl::Send( const AnyEvent& event )
{
    this->PostEvent( event );
}


///////////////////////////////////////////////////////////////////////////////
//
// State
//

State::State( StatePtr impl )
    : m_impl( impl )
{
}


State& State::EnterAction( Action action )
{
    CARAMEL_CHECK( ! m_impl->m_enterAction );

    m_impl->m_enterAction = action;
    return *this;
}


State& State::ExitAction( Action action )
{
    CARAMEL_CHECK( ! m_impl->m_exitAction );

    m_impl->m_exitAction = action;
    return *this;
}


State& State::Transition( Int eventId, Int targetStateId, Action action )
{
    auto transition = std::make_shared< Statechart::Transition >( targetStateId, action );
    if ( ! m_impl->m_transitions.Insert( eventId, transition ))
    {
        CARAMEL_THROW(
            "%s transition duplicate, eventId: %d, targetStateId: %d",
            m_impl->GetName(), eventId, targetStateId
        );
    }

    return *this;
}


//
// Implementation
//

StateImpl::StateImpl( Int stateId, const std::string& machineName )
    : m_id( stateId )
    , m_name( Sprintf( "Machine[%s].State[%d]", machineName, stateId ))
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel
