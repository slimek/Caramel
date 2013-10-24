// Caramel C++ Library - Statechart Facility - State Machine Header

#ifndef __CARAMEL_STATECHART_STATE_MACHINE_H
#define __CARAMEL_STATECHART_STATE_MACHINE_H

#include <Caramel/Caramel.h>

#if defined( CARAMEL_COMPILER_HAS_PRAGMA_ONCE )
#pragma once
#endif

#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Statechart/State.h>


namespace Caramel
{

namespace Statechart
{

///////////////////////////////////////////////////////////////////////////////
//
// State Machine
//

class StateMachineImpl;

class StateMachine
{
public:

    explicit StateMachine( const std::string& name );
    ~StateMachine();

    //
    // Build this state machine.
    // - This function can only be used before calling Initiate().
    //
    State AddState( Int stateId );

    //
    // Start this state machine, enter the initial state.
    //
    void Initiate( Int stateId );

    //
    // Enqueue this event for later processing.
    //
    void PostEvent( Int eventId );

    //
    // Process enqueued events.
    // - Call this function ONLY when you using the built-in TaskPoller.
    // - If no event exists, it returns immediately.
    //   If some events exist, process at least one event,
    //   then process the rest events until empty, or until slice ticks spent.
    //
    void Process( const Ticks& sliceTicks = Ticks::Zero() );


    /// Properties ///

    Int GetCurrentStateId() const;


private:

    std::unique_ptr< StateMachineImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel

#endif // __CARAMEL_STATECHART_STATE_MACHINE_H
