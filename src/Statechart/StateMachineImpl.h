// Caramel C++ Library - Statechart Facility - State Machine Private Header

#ifndef __CARAMEL_STATECHART_STATE_MACHINE_IMPL_H
#define __CARAMEL_STATECHART_STATE_MACHINE_IMPL_H
#pragma once

#include <Caramel/Caramel.h>
#include "Statechart/StateImpl.h"
#include "Statechart/Transition.h"
#include <Caramel/Concurrent/HashMap.h>
#include <Caramel/Statechart/StateMachine.h>
#include <Caramel/Task/TaskPoller.h>
#include <Caramel/Thread/ThreadId.h>
#include <mutex>


namespace Caramel
{

namespace Statechart
{

///////////////////////////////////////////////////////////////////////////////
//
// State Machine
//

class StateMachineImpl
{
    friend class StateMachine;

public:

    explicit StateMachineImpl( const std::string& name );

    void ProcessEvent( const AnyEvent& evt );

    void DoTransit( TransitionPtr transition, StatePtr targetState );


    //
    // Timer
    // - StartTimer() starts a timer of current state.
    //   This timer would be cancelled when exiting the current state.
    // - CancelTimer() would cancel the current timer, if exists.
    //
    void StartTimer( const Ticks& ticks );
    void CancelTimer();


private:

    /// Internal Functions ///

    void EnterState();
    void ExitState();


    /// Data Members ///

    std::string m_name;

    TaskExecutor* m_taskExecutor;
    std::unique_ptr< TaskPoller > m_builtinTaskPoller;

    typedef Concurrent::HashMap< Int, StatePtr > StateMap;
    StateMap m_states;

    Bool     m_initiated;
    StatePtr m_currentState;

    Uint      m_transitNumber;     // How many times of transition.
    TickPoint m_currentStartTime;  // The start time of current state.

    ThreadId m_actionThreadId;
    AnyEvent m_activeEvent;

    std::mutex m_mutex;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel

#endif // __CARAMEL_STATECHART_STATE_MACHINE_IMPL_H
