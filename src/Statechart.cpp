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


StateMachine::StateMachine( const std::string& name, TaskExecutor& executor )
    : m_impl( new StateMachineImpl( name, executor ))
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
        CARAMEL_THROW( "Initial state not found, machine: %s, stateId: %d",
                       m_impl->m_name, stateId );
    }

    // All target states of transitions must exist.
    // Throws if verify failed.
    m_impl->VerifyStatesAndTransitions();

    m_impl->PostInitiate( initialState );

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


void StateMachine::PostEvent( Int eventId, Any&& value )
{
    this->PostEvent( AnyEvent( eventId, std::move( value )));
}


void StateMachine::PostEvent( const AnyEvent& evt )
{
    m_impl->PostEvent( evt );
}


void StateMachine::PlanToTransit( Int stateId )
{
    m_impl->PlanToTransit( stateId );
}


void StateMachine::StartTimer( const Ticks& ticks, Int eventId )
{
    m_impl->StartTimer( ticks, eventId );
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
    , m_reacting( false )
{
    m_taskExecutor = m_builtinTaskPoller.get();
}


StateMachineImpl::StateMachineImpl( const std::string& name, TaskExecutor& executor )
    : m_name( name )
    , m_taskExecutor( &executor )
    , m_initiated( false )
    , m_transitNumber( 0 )
    , m_reacting( false )
{
}


//
// Building
//

void StateMachineImpl::VerifyStatesAndTransitions()
{
    // Verification:
    //   All target states of transitions must exist in this machine.

    const auto states = m_states.GetValuesSnapshot();

    for ( StatePtr state : states )
    {
        const auto transitions = state->m_transitions.GetValuesSnapshot();

        for ( TransitionPtr transition : transitions )
        {
            if ( ! m_states.Contains( transition->targetStateId ))
            {
                CARAMEL_THROW( "Transition target state not found, machine: %s, stateId: %d",
                               m_name, transition->targetStateId );
            }
        }
    }
}


//
// Events and Transitions
//

void StateMachineImpl::PostInitiate( StatePtr initialState )
{
    auto task = MakeTask(
        Sprintf( "Machine[%s].ProcessInitiate", m_name ),
        [=] { this->ProcessInitiate( initialState ); }
    );

    this->m_taskExecutor->Submit( task );
}


void StateMachineImpl::ProcessInitiate( StatePtr initialState )
{
    // Initate a machine would trigger the enter action of the initial state.

    LockGuard lock( m_mutex );

    m_actionThreadId = ThisThread::GetId();
    auto tidGuard = ScopeExit( [=] { m_actionThreadId = ThreadId(); } );

    m_currentState = initialState;

    this->EnterState();
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


    /// Transition ///

    TransitionPtr transition;
    if ( m_currentState->m_transitions.Find( evt.Id(), transition ))
    {
        StatePtr targetState;
        CARAMEL_VERIFY( m_states.Find( transition->targetStateId, targetState ));

        this->DoTransit( targetState, transition->action );
        return;
    }


    /// Reaction ///

    Action reaction;
    if ( m_currentState->m_reactions.Find( evt.Id(), reaction ))
    {
        this->DoInStateReact( evt.Id(), reaction );

        if ( m_transitionPlan )
        {
            const Int stateId = m_transitionPlan.get();
            m_transitionPlan = boost::none;

            StatePtr targetState;
            if ( ! m_states.Find( stateId, targetState ))
            {
                CARAMEL_THROW(
                    "%s reaction plan to transit, but target state not found, "
                    "eventId: %d, target stateId: %d",
                    m_currentState->GetName(), evt.Id(), stateId
                );
            }

            this->DoTransit( targetState, Action() );
        }

        return;
    }

    // Otherwise, discard this event
    CARAMEL_TRACE_DEBUG( "%s discards event %d", m_currentState->GetName(), evt.Id() );
}


void StateMachineImpl::DoTransit( StatePtr targetState, const Action& transitionAction )
{
    // REMARKS: At this point, the m_mutex should have been locked.

    this->ExitState();

    if ( transitionAction )
    {
        auto xc = CatchException( [&] { transitionAction(); } );
        if ( xc )
        {
            CARAMEL_TRACE_WARN(
                "%s transition action throws, target stateId: %d\n%s",
                m_currentState->GetName(), targetState->GetId(), xc.TracingMessage()
            );
        }
    }

    m_currentState = targetState;

    this->EnterState();
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
}


void StateMachineImpl::ExitState()
{
    if ( m_timerTask.IsValid() )
    {
        m_timerTask.Cancel();
        m_timerTask = Task< void >();  // Clear the timer.
    }

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


void StateMachineImpl::DoInStateReact( Int eventId, const Action& action )
{
    m_reacting = true;
    auto guard = ScopeExit( [=] { m_reacting = false; } );

    m_transitionPlan = boost::none;

    auto xc = CatchException( [=] { action(); } );
    if ( xc )
    {
        CARAMEL_TRACE_WARN( "%s reaction to event %d throws:\n%s",
                            m_currentState->GetName(), eventId, xc.TracingMessage() );
    }
}


void StateMachineImpl::PlanToTransit( Int stateId )
{
    if ( ! m_reacting || m_actionThreadId != ThisThread::GetId() )
    {
        CARAMEL_THROW( "PlanToTransit() can only be called in a reaction" );
    }

    if ( m_transitionPlan )
    {
        CARAMEL_THROW( "You have already set to transit in this reaction" );
    }

    m_transitionPlan = stateId;
}


void StateMachineImpl::StartTimer( const Ticks& ticks, Int eventId )
{
    if ( m_actionThreadId != ThisThread::GetId() )
    {
        CARAMEL_THROW( "StartTimer() can only be called in an action" );
    }

    if ( m_timerTask.IsValid() )
    {
        CARAMEL_THROW( "You have already set a timer in this state" );
    }

    m_timerTask = MakeTask(
        Sprintf( "%s.TimerEvent[%d]", m_currentState->GetName(), eventId ),
        [=] { this->ProcessEvent( AnyEvent( eventId )); }
    );
    m_timerTask.DelayFor( ticks );

    this->m_taskExecutor->Submit( m_timerTask );
}


//
// Implements AnyEventTarget
//

AnyEventTargetPtr StateMachine::GetTargetImpl() const
{
    return m_impl;
}


void StateMachineImpl::Send( const AnyEvent& event, Uint age )
{
    UniqueLock ulock = this->CompareAge( age );
    if ( ulock )
    {
        this->PostEvent( event );
    }
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

    m_impl->m_enterAction = std::move( action );
    return *this;
}


State& State::ExitAction( Action action )
{
    CARAMEL_CHECK( ! m_impl->m_exitAction );

    m_impl->m_exitAction = std::move( action );
    return *this;
}


State& State::Transition( Int eventId, Int targetStateId, Action action )
{
    // Check the Event ID
    if ( m_impl->m_reactions.Contains( eventId ))
    {
        CARAMEL_THROW(
            "%s transition conflicts with reactions, eventId: %d, targetStateId: %d",
            m_impl->GetName(), eventId, targetStateId 
        );
    }

    // Insert the Transition
    auto transition = std::make_shared< Statechart::Transition >( targetStateId, std::move( action ));
    if ( ! m_impl->m_transitions.Insert( eventId, transition ))
    {
        CARAMEL_THROW( "%s transition duplicate, eventId: %d, targetStateId: %d",
                       m_impl->GetName(), eventId, targetStateId );
    }

    return *this;
}


State& State::Reaction( Int eventId, Action action )
{
    // Check the Event ID
    if ( m_impl->m_transitions.Contains( eventId ))
    {
        CARAMEL_THROW( "%s reaction conflicts with transitions, eventId: %d",
                       m_impl->GetName(), eventId );
    }

    // Insert Reaction
    if ( ! m_impl->m_reactions.Insert( eventId, std::move( action )))
    {
        CARAMEL_THROW( "%s reaction duplicate, eventId: %d",
                       m_impl->GetName(), eventId );
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
