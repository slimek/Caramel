// Caramel C++ Library - Statechart Facility - Implementation

#include <Caramel/CaramelPch.h>

#include <Caramel/Error/CatchException.h>
#include <Caramel/Functional/ScopeExit.h>
#include <Caramel/Statechart/StateImpl.h>
#include <Caramel/Statechart/StateMachineImpl.h>
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
}


//
// Operations
//

State StateMachine::AddState( Int stateId )
{
    StatePtr newState = std::make_shared< StateImpl >( stateId );
    if ( ! m_impl->m_states.Insert( stateId, newState ))
    {
        CARAMEL_THROW( "State duplicate, machine: %s, stateId: %d", m_impl->m_name, stateId );
    }
    return State( newState );
}


void StateMachine::Initiate( Int stateId )
{
    StatePtr initialState;
    if ( ! m_impl->m_states.Find( stateId, initialState ))
    {
        CARAMEL_THROW( "State not found, machine: %s, stateId: %d", m_impl->m_name, stateId );
    }

    Task task(
        Sprintf( "Machine[%s].ProcessInitiate[%d]", m_impl->m_name, stateId ),
        [=] { m_impl->ProcessInitiate( initialState ); }
    );

    m_impl->m_taskExecutor->Submit( task );
}


//
// Implementation
//

StateMachineImpl::StateMachineImpl( const std::string& name )
    : m_name( name )
    , m_taskExecutor( new TaskPoller )
    , m_transitNumber( 0 )
    , m_actionThreadId( 0 )
{
}


void StateMachineImpl::ProcessInitiate( StatePtr initialState )
{
    auto ulock = UniqueLock( m_mutex );

    m_actionThreadId = ThisThread::GetThreadId();
    auto guard = ScopeExit( [=] { m_actionThreadId = 0; } );

    m_currentState = initialState;

    this->EnterState();
}


void StateMachineImpl::StartTimer( const TickDuration& ticks )
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
            CARAMEL_TRACE_WARN(
                "Enter action throws, machine: %s, stateId: %d", m_name, m_currentState->m_id );
        }
    }

    if ( TickDuration::Zero() < m_currentState->m_autoTimerDuration )
    {
        this->StartTimer( m_currentState->m_autoTimerDuration );
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
    CARAMEL_ASSERT( ! m_impl->m_enterAction );

    m_impl->m_enterAction = action;
    return *this;
}


//
// Implementation
//

StateImpl::StateImpl( Int stateId )
    : m_id( stateId )
{
}


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel
