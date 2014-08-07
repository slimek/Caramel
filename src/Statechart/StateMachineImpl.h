// Caramel C++ Library - Statechart Facility - State Machine Private Header

#ifndef __CARAMEL_STATECHART_STATE_MACHINE_IMPL_H
#define __CARAMEL_STATECHART_STATE_MACHINE_IMPL_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include "Async/AnyEventTargetImpl.h"
#include "Statechart/StateImpl.h"
#include "Statechart/Transition.h"
#include <Caramel/Concurrent/HashMap.h>
#include <Caramel/Statechart/StateMachine.h>
#include <Caramel/Task/TaskPoller.h>
#include <Caramel/Thread/ThreadId.h>
#include <boost/optional.hpp>
#include <mutex>


namespace Caramel
{

namespace Statechart
{

///////////////////////////////////////////////////////////////////////////////
//
// State Machine
//

class StateMachineImpl : public AnyEventTargetImpl
{
    friend class PromptStateMachine;
    friend class StateMachine;

public:

    explicit StateMachineImpl( const std::string& name );
    StateMachineImpl( const std::string& name, TaskExecutor& executor );


    /// Building Machine ///

    State AddState( Int stateId );
    void Initiate( Int stateId );


    /// Events and Transitions ///

    void ProcessInitiate( StatePtr initialState );

    void PostEvent( const AnyEvent& event );
    void ProcessEvent( const AnyEvent& event );

    void DoTransit( StatePtr targetState, const Action& transitionAction );
    void DoInStateReact( Int eventId, const Action& action );

    void PlanToTransit( Int stateId );

    void StartTimer( const Ticks& ticks, Int eventId );

    
    // This function is valid only when the executor is built-in.
    void PollAllEvents();


    /// Implements AnyEventTargetImpl ///

    void Send( const AnyEvent& event, Uint age ) override;


private:

    /// Internal Functions ///

    void VerifyStatesAndTransitions();

    void EnterState();
    void ExitState();


    /// Data Members ///

    std::string m_name;

    TaskExecutor* m_taskExecutor;
    std::unique_ptr< TaskPoller > m_builtinTaskPoller;

    typedef Concurrent::HashMapWithSnapshot< Int, StatePtr > StateMap;
    StateMap m_states;

    Bool     m_initiated;
    StatePtr m_currentState;

    Uint      m_transitNumber;     // How many times of transition.
    TickPoint m_currentStartTime;  // The start time of current state.

    ThreadId m_actionThreadId;
    AnyEvent m_activeEvent;

    Bool     m_reacting;  // Executing a reaction.

    // This is set by PlanToTransit(), 
    // which can only be called in a reaction.
    boost::optional< Int > m_transitionPlan;

    Task< void > m_timerTask;

    std::mutex m_mutex;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel

#endif // __CARAMEL_STATECHART_STATE_MACHINE_IMPL_H
