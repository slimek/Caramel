// Caramel C++ Library - Statechart Facility - State Machine Header

#ifndef __CARAMEL_STATECHART_STATE_MACHINE_H
#define __CARAMEL_STATECHART_STATE_MACHINE_H
#pragma once

#include <Caramel/Setup/CaramelDefs.h>
#include <Caramel/Async/AnyEventTarget.h>
#include <Caramel/Chrono/TickClock.h>
#include <Caramel/Statechart/State.h>
#include <Caramel/Task/TaskFwd.h>
#include <boost/noncopyable.hpp>


namespace Caramel
{

namespace Statechart
{

///////////////////////////////////////////////////////////////////////////////
//
// State Machine
//

class StateMachineImpl;

class StateMachine : public AnyEventTarget
                   , public boost::noncopyable
{
public:

    explicit StateMachine( const std::string& name );
    StateMachine( const std::string& name, TaskExecutor& executor );
    ~StateMachine();


    // Build this state machine.
    // - This function can only be used before calling Initiate().
    State AddState( Int stateId );

    
    // Start this state machine, enter the initial state.
    // - This function submit a task. In the task the enter action
    //   of the initial state would be triggered.
    void Initiate( Int stateId );


    // Enqueue an event for later processing.
    void PostEvent( Int eventId );
    void PostEvent( Int eventId, const Any& value );
    void PostEvent( Int eventId, Any&& value );
    void PostEvent( const AnyEvent& anyEvent );


    // Plan to Transit to another state.
    // - This function should only be called in an in-state reaction.
    //   It doesn't transit immediately, but will start to transit
    //   after the reaction returns.
    void PlanToTransit( Int stateId );


    // Process enqueued events.
    // - Call this function ONLY when you using the built-in TaskPoller.
    // - If no event exists, it returns immediately.
    //   If some events exist, process at least one event,
    //   then process the rest events until empty, or until slice ticks spent.
    void Process( const Ticks& sliceTicks = Ticks::Zero() );


    /// Properties ///

    Int GetCurrentStateId() const;

    // Return the event to cause the current action.
    // - When you are not in an action handler, this returns a "not an event" event.
    AnyEvent GetActiveEvent() const;


private:

    /// Implements AnyEventTarget ///

    AnyEventTargetPtr GetTargetImpl() const override;


    std::shared_ptr< StateMachineImpl > m_impl;
};


///////////////////////////////////////////////////////////////////////////////

} // namespace Statechart

} // namespace Caramel

#endif // __CARAMEL_STATECHART_STATE_MACHINE_H
