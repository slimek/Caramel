// Caramel C++ Library - Statechart Facility - State Machine Header

#ifndef __CARAMEL_STATECHART_STATE_MACHINE_H
#define __CARAMEL_STATECHART_STATE_MACHINE_H
#pragma once

#include <Caramel/Caramel.h>
#include <Caramel/Async/AnyEvent.h>
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

    // Build this state machine.
    // - This function can only be used before calling Initiate().
    State AddState( Int stateId );

    
    // Start this state machine, enter the initial state.
    void Initiate( Int stateId );

    // Enqueue an event for later processing.
    void PostEvent( Int eventId );
    void PostEvent( Int eventId, const Any& value );
    void PostEvent( const AnyEvent& anyEvent );


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

    // Return the event to cause the current action.
    // - When you are not in an action handler, this returns a "not an event" event.
    AnyEvent GetActiveEvent() const;


private:

    std::unique_ptr< StateMachineImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel

#endif // __CARAMEL_STATECHART_STATE_MACHINE_H
