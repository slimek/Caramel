// Caramel C++ Library - Statechart Facility - State Machine Private Header

#ifndef __CARAMEL_STATECHART_STATE_MACHINE_IMPL_H
#define __CARAMEL_STATECHART_STATE_MACHINE_IMPL_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Concurrent/Map.h>
#include <Caramel/Statechart/StateMachine.h>
#include <Caramel/Task/TaskPoller.h>
#include <mutex>


namespace Caramel
{

namespace Statechart
{

///////////////////////////////////////////////////////////////////////////////
//
// State Machine
//

class StateImpl;
typedef std::shared_ptr< StateImpl > StatePtr;

class StateMachineImpl
{
    friend class StateMachine;

public:

    explicit StateMachineImpl( const std::string& name );

    void ProcessInitiate( StatePtr initialState );

    void ProcessEvent( Int eventId );

    void DoTransit( StatePtr targetState );


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
    

    typedef Concurrent::Map< Int, StatePtr > StateMap;
    StateMap m_states;

    StatePtr m_currentState;

    Uint      m_transitNumber;     // How many times of transition.
    TickPoint m_currentStartTime;  // The start time of current state.

    Uint m_actionThreadId;

    std::mutex m_mutex;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel

#endif // __CARAMEL_STATECHART_STATE_MACHINE_IMPL_H
